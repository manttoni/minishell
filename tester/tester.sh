#!/bin/bash
FAIL=0
while IFS= read -r line; do
	bout=$(bash <<< "$line")
	mout=$(../minishell <<< "$line" | grep -v "minishell>")
	if [ "$bout" != "$mout" ]; then
		FAIL=1
		echo "----------------------------"
		echo "input: $line"
		diff <(echo "$bout") <(echo "$mout")
	fi
done < input.txt
if [ $FAIL == 0 ]; then
	echo "all tests passed!"
fi

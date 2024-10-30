#!/bin/bash
FAIL=0

if ls ../ | grep -q "minishell"; then
	echo "-----------------"
	echo "Minishell tester:"
	echo "-----------------"
else
	echo "../minishell not found"
	exit 1
fi

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

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

echo "Testing parser..."

while IFS= read -r line; do
	bout=$(bash <<< "$line")
	mout=$(../minishell <<< "$line" | grep -v "minishell>")
	if [ "$bout" != "$mout" ]; then
		FAIL=1
		echo "----------------------------"
		echo "input: $line"
		diff <(echo "$bout") <(echo "$mout")
	fi
done < echotest.txt
if [ $FAIL == 0 ]; then
	echo "All tests passed!"
fi

echo "--------------------"

###############################################################################

echo "Testing builtins..."
FAIL=0

while IFS= read -r line; do
	input=$(echo -e "$line")
	bout=$(bash <<< "$input")
	mout=$(../minishell <<< "$input" | grep -v "minishell>")
	if [ "$bout" != "$mout" ]; then
		FAIL=1
		echo "----------------------------"
		echo "input: $line"
		diff <(echo "$bout") <(echo "$mout")
	fi
done < builtintest.txt
if [ $FAIL == 0 ]; then
	echo "All tests passed!"
fi

echo "--------------------"

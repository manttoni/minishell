#!/bin/bash
FAIL=0

if ls ../ | grep -q "minishell"; then
	echo "=========================="
	echo "==  Minishell  tester:  =="
	echo "=========================="
else
	echo "../minishell not found"
	exit 1
fi

echo "  *** Testing parser ***"

while IFS= read -r line; do
	bash_out=$(bash <<< "$line" 2>/dev/null)
	minishell_out=$(../minishell <<< "$line" 2>/dev/null| grep -v "minishell>")
	if [ "$bash_out" != "$minishell_out" ]; then
		FAIL=1
		echo "----------------------------"
		echo "input: $line"
		diff <(echo "$bash_out") <(echo "$minishell_out")
	fi
done < echotest.txt
if [ $FAIL == 0 ]; then
	echo " 🥳 All tests passed! 🥳"
fi

echo "=========================="

###############################################################################

echo " *** Testing builtins ***"
FAIL=0

while IFS= read -r line; do
	input=$(echo -e "$line")
	bash_out=$(bash <<< "$input" 2>/dev/null)
	minishell_out=$(../minishell <<< "$input" 2>/dev/null | grep -v "minishell>" 2>/dev/null)
	if [ "$bash_out" != "$minishell_out" ]; then
		FAIL=1
		echo "--------------------------"
		echo "input: $line"
		diff <(echo "$bash_out") <(echo "$minishell_out")
	fi
done < builtintest.txt
if [ $FAIL == 0 ]; then
	echo " 🥳 All tests passed! 🥳"
fi

echo "=========================="

##############################################################################

echo "     *** Testing > ***"
FAIL=0

while IFS= read -r line; do
	input=$(echo -e "$line")
	mkdir testfiles
	bash <<< "$input" 2>/dev/null > testfiles/bashfdout.txt
	../minishell <<< "$input" 2>/dev/null | grep -v "minishell>" > testfiles/minishellfdout.txt
	diff testfiles/bashfdout.txt testfiles/minishellfdout.txt
	if [ $? -eq 1 ]; then
		echo "input: $input"
		FAIL=1
	fi
	rm -rf testfiles
done < builtintest.txt
if [ $FAIL == 0 ]; then
	echo " 🥳 All tests passed! 🥳"
fi

echo "=========================="


#!/bin/bash

cd ..
make re
cd tester

if ! ls ../ | grep -q "minishell"; then
	echo "../minishell not found"
	exit 1
fi

if ! ls | grep -q "logs"; then
	mkdir logs
fi

mkdir td # test directory, sandbox for creating files

miniout=logs/mini.log
bashout=logs/bash.log
valgout=logs/valgrind.log
difflog=logs/diff.log
>$miniout
>$bashout
>$valgout
>$difflog

testseparator="~~~~~~~~~~~~~~~~~~~~~"

len=$(wc -l < input.txt)
i=1

while read -r line; do
	input=$(echo -e "$line")
	echo "input: $line" >>$miniout
	echo "input: $line" >>$bashout

	../minishell <<< "$input" 2>/dev/null | grep -v "minishell>" >>$miniout
	valgrind -q --suppressions=../supp.supp --log-file=$valgout --leak-check=full --show-leak-kinds=all ../minishell <<< "$input" >/dev/null 2>/dev/null
	bash <<< "$input" 2>/dev/null >>$bashout

	if [ -t 1 ]; then
		percent=$(( 100 * i / len ))
		errors=$(diff -U 1 "$miniout" "$bashout" | grep input: | wc -l)
		echo -ne "[                        ] Errors: "$errors"\r"
		echo -ne "           $percent%\r"
		echo -ne "[----------$percent%----------]" | head -c $((1 + percent * 24 / 100))
		echo -ne "\r"
		i=$((i + 1))
	fi

	echo "$testseparator" >>$miniout
	echo "$testseparator" >>$bashout
done < input.txt

echo -e "\nResults:"

if diff -U 1 "$miniout" "$bashout" > $difflog && [ ! -s "$valgout" ]; then
	echo "🥳 All tests passed! 🥳   "
fi
if [ -s "$valgout" ]; then
	echo "Check logs/valgrind.log for errors"
fi
if [ -s "$difflog" ]; then
	echo "Check logs/diff.log for errors"
fi

rm -rf td

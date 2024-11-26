#!/bin/bash

if ! ls ../ | grep -q "minishell"; then
	echo "../minishell not found"
	exit 1
fi

if ! ls | grep "logs"; then
	mkdir logs
fi

miniout=logs/mini.log
bashout=logs/bash.log
valgout=logs/valgrind.log
>$miniout
>$bashout
>$valgout

len=$(wc -l < input.txt)
i=1

while IFS= read -r line; do
	input=$(echo -e "$line")
	echo "input: $line" >>$miniout
	echo "input: $line" >>$bashout

	../minishell <<< "$input" 2>/dev/null | grep -v "minishell>" >>$miniout
	valgrind -q --suppressions=../supp.supp --log-file=$valgout --leak-check=full --show-leak-kinds=all ../minishell <<< "$input" >/dev/null 2>/dev/null
	bash <<< "$input" 2>/dev/null >>$bashout

	percent=$(( 100 * i / len ))
	echo -ne "[                        ]\r"
	echo -ne "           $percent%\r"
	echo -ne "[----------$percent%----------]" | head -c $((1 + percent * 24 / 100))
	echo -ne "\r"

	i=$((i + 1))
done < input.txt

echo -e "\nResults:"

if diff -u "$miniout" "$bashout" && [ ! -s "$valgout" ]; then
	echo "🥳 All tests passed! 🥳   "
fi
if [ -s "$valgout" ]; then
	echo "Check logs/valgrind.log for errors"
fi

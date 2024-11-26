bash_out=bash_out.log
minishell_out=minishell_out.log
>$bash_out
>$minishell_out
while IFS= read -r line; do


	echo "input: $line" >>$bash_out
	echo "input: $line" >>$minishell_out

	bash <<< "$line" 2>/dev/null >>$bash_out
	../minishell <<< "$line" 2>/dev/null | grep -v "minishell>" >>$minishell_out
done < echotest.txt

diff "$bash_out" "$minishell_out"

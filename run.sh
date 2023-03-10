#!/bin/bash
#valgrind --suppressions=valgrind_ignore_leaks.txt --log-file=valgrind-out.txt ./minishell
valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=valgrind_ignore_leaks.txt --log-file=valgrind-out.txt ./minishell
#valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --suppressions=valgrind_ignore_leaks.txt --log-file=valgrind-out.txt ./minishell
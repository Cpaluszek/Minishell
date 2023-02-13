# MiniShell
MiniShell is an introduction to the world of shells, which provide a convenient text interface to interact with your system. Shells might seem very easy to understand but have very specific and defined behaviour in almost every single case, most of which will need to be handled properly.

## Mandatory Part
```
External functs. readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```

**The shell should:**
- Display a **prompt** when waiting for a new command.
- Have a working **history**.
- Search and launch the right executable (based on the `PATH` variable or using a
    relative or an absolute path).
- Not use more than **one global variable**. Think about it. You will have to explain
    its purpose.
- Not interpret unclosed quotes or special characters which are not required by the
    subject such as `\` (backslash) or `;` (semicolon).
- Handle `’`(single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle `"` (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$` (dollar sign).
    
Implement **redirections** :

- `<` should redirect input.
- `>` should redirect output.
- `<<` should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
- `>>` should redirect output in append mode.

Implement **pipes** (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

Handle **environment variables** (`$` followed by a sequence of characters) which should expand to their values.

Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.

Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like inbash.
- In interactive mode:

    - `ctrl-C` displays a new prompt on a new line.
    - `ctrl-D` exits the shell.
    - `ctrl-\`does nothing.

- Your shell must implement the following **builtins** :

    - `echo` with option `-n`
    - `cd` with only a relative or absolute path
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options

## Bonus Part

Your program has to implement:

- `&&` and `||` with parenthesis for priorities.
- Wildcards `*` should work for the current working directory.


## Resources
- [00 MINISHELL WIKI · AudeizReading/minishell Wiki](https://github.com/AudeizReading/minishell/wiki/00--MINISHELL----WIKI)
- [iciamyplant/Minishell: This is my final 42's project Minishell, I implemented my own shell in C, which supports redirections, pipes, environment variables and several builtins](https://github.com/iciamyplant/Minishell)

### Shell
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

**Writing your own shell:**
- [Chapter5-WritingYourOwnShell.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Swoorup/mysh: A basic unix shell interpreter in c programming language using recursive descent parser.](https://github.com/Swoorup/mysh)
- [LucieLeBriquer: minishell](https://github.com/LucieLeBriquer/minishell)

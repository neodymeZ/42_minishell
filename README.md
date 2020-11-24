# 42_minishell
Creating a shell which is a subset of bash

## Usage
```
git clone <repo> <dir>
cd dir
make
./minishell
```

## Features
1. Prompt while waiting for a new command;
2. Searching and launching executables (full path, or searched in $PATH);
3. Builtins (echo, cd, pwd, export, unset, env, exit);
4. Lists of commands (;);
5. Pipes (|);
6. Quoted strings (single or double quoted);
7. Input/output redirections (>, <, >>);
8. Environment variables expansion;
9. Handling return value and $? variable;
10. Handling SIGINT and SIQUIT signals;
11. Handling EOF (Ctrl-D);
12. Multiline strings with \ or incomplete quotes;
13. Escaping characters in quoted or unquoted strings with '\';

## Known bugs 
Behavior, not identical to bash:

1. Already input symbols could not be deleted after Ctrl-D.

*Reason: input is handled in cooked mode, not char mode (as in bash).*

2. If syntax error occurs in a command list (;), commands before the erroneous one 
are executed (in bash, only error is shown).

*Reason: input is parsed and the command is launched for every command in the list
independently. Bash uses pre-parsing step to check the input string for syntax errors.*

3. Commands, saved in env vars, are not launched on $VAR command.

*Reason: bash expands environment variables on an earlier stage, before parsing.*

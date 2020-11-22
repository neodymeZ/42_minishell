# 42_minishell
42 minishell project

To do:
1) Word expansion (escape chars?)
2) Uppercase letters in commands

To fix:
1) Check memory leaks ✅ 
2) Changing $PATH after cd ✅
3) Sorting export output, not env array ✅
4) Segfault on redir-only command (> test)
5) Handle multiple semicolons as invalid sequence
6) !!Launch commands in lists in parent process, not in children
7) Clear input line when SIGINT is sent in multiline
8) Escape characters ✅
9) Handle UPPERCASE when running builtins

Additionally implemented:
1) Multiline input (on '\' symbol or on missing quote);

Will not be implemented:
1) Multiline pipe (complex parsing of input is needed);
2) Shell variables;
3) Simultaneous command execution. Commands are executed sequentially,
the parent process waits until completion before forking a new child.
Thus, looped commands like "yes" won't work correctly in pipes (i.e. yes | head)
4) Launching script as a command line argument (not required by subject)

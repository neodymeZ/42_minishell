# 42_minishell
42 minishell project

To do:
✅ 1) Parser - token string concatenation
✅ 2) Word expansion (env vars substitution
3) Word expansion (escape chars?)
3) Pipes
4) Redirections
5) Error management - pass error description to errman function
   for custom error messages
6) Check memory leaks
7) Uppercase letters in commands?
8) Launching script as a command line argument?

Additionally implemented:
1) Multiline input (on '\' symbol or on missing quote);

Will not be implemented:
1) Multiline pipe (complex parsing of input is needed);
2) Freeing memory on erroneous exit (OS will handle);
3) Shell variables;

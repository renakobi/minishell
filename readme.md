tokenization: separate commands into categories(tokens) 
where there are 9 token types total:
1. Command: echo, ls, grep, etc... (there are a few special case commands)
2. Argument: a word or a flag like a string: "hello" -l -c etc...
3. Pipe: |
4. In descriptor(redirection): < 
5. Out descriptor(redirection): >
6. Heredoc redirection: reads from text until eof is reached(eof end of file) <<
7. redirection append: adds string at the end of the file >>
8. paranthesis: ()
9. EOF: end of file: usually NULL terminator but can be anything


Tokenization needs to be hardcoded using/ but not limited to the following:
1. Strcmp
2. Strnchr
3. ft_split (modified)
4. Tokenizer

ft_split methodology:
split has to have 3 kinds of separators: space, single quote '', and double quote ""

Tokenizer methodology:
It should classify the raw data into categories using hardcoded statements since no c function
can aid and there is no method more efficient and not overkill than hardcoding it

Error handling:
Since it is hardcoded, it needs to handle all the errors of invalid syntax and invalid input and invalid mix of tokens (| ls| grep > < "">)
This is handled in parsing

For signals: ctrl keys and esc: tcsetattr() is used: ctrl-c sends SIGIN (in signal) and ctrl-v signals EOF (end of file)
them and the rest use: tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

For arrow keys: they use esc sequences "returned value"
1. Up ↑	\033[A
2. Down ↓ \033[B
3. Right → \033[C
4. Left ← \033[D
5. ESC  \033

tasks/timeline:

    Week 1 — Core Setup
Project structure & Makefile
Input reading (readline / manual read)
Signal handling (Ctrl-C, Ctrl-D, SIGQUIT)

    Week 2 — Lexing & Parsing
Tokenizer for commands, pipes, redirections, quotes
Syntax validation
Build command tree / execution structure

    Week 3 — Execution Engine
Run simple commands with execve()
Path resolution using $PATH
Pipeline support with pipe() and fork()

    Week 4 — Features & Polish
Implement redirections and heredoc
Add builtins (cd, echo, pwd, env, export, unset, exit)
Environment variable expansion ($VAR, $?)
Testing, memory cleanup, error messages

📅 Week 1 – Foundations and Parsing Basics

Goal: Get the shell to read, parse, and display commands properly.

Tasks

✅ Understand subject + requirements (signals, leaks, builtins, etc.)

✅ Set up Makefile, libft, header files, struct definitions

✅ Integrate readline and command loop

✅ Implement basic tokenizer (split input by spaces, handle quotes)

✅ Handle simple commands (no pipes, no redirections)

✅ Implement signal handling (SIGINT, SIGQUIT behavior)

Division

A (Core): Setup project structure, readline loop, signals, prompt design

B (Parsing): Tokenizer, handling quotes ' and " correctly, trimming spaces

Expected Time

5–6 days total (around 25–30 hours of work)

📅 Week 2 – Execution and Environment Handling

Goal: Make your shell actually run commands and handle environment variables.

Tasks

✅ Implement environment management (copy envp, export, unset)

✅ Implement $VAR and $? expansions

✅ Use execve to execute binaries in PATH

✅ Implement builtins: echo, pwd, env, exit

✅ Manage child processes and return status codes

Division

A: Implement executor (fork, execve, waitpid, PATH search)

B: Implement environment system + expansion logic

Expected Time

5–6 days
(You should be able to type commands like ls, pwd, echo $HOME and see correct results)

📅 Week 3 – Pipes, Redirections, and Advanced Parsing

Goal: Support multi-command structures like ls | grep txt > out.txt.

Tasks

✅ Implement redirections: <, >, >>, << (heredoc)

✅ Implement pipes

✅ Connect parser to executor (AST or command list)

✅ Handle edge cases: unclosed quotes, syntax errors

✅ Add builtins: cd, export, unset if not done yet

Division

A: Pipes and file descriptors (dup2, pipe management)

B: Redirections (input/output/append/heredoc)

Expected Time

5–6 days

📅 Week 4 – Testing, Debugging, and Memory Cleanup

Goal: Make the shell stable, leak-free, and compliant.

Tasks

✅ Refactor and clean up

✅ Handle edge cases (e.g., empty input, Ctrl+D)

✅ Test all builtins and expansions

✅ Run Valgrind and fix leaks

✅ Final signal behavior polish

✅ Prepare for evaluation checklist

Division

A: Valgrind, leaks, signals, error messages

B: Testing, edge case handling, command syntax validation

Expected Time

4–5 days

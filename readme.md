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

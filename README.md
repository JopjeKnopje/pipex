# Pipex
## 42 Pipex project

Simulating the shell's pipe operator


## Resources
* https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY


## Notes
* Local executables are not required to be handled.


## TODO
[ ] Check if the command given to pipex contains the abolute path ex. (/usr/bin/prog)
[ ] Check if the command given to pipex contains the relative path ex. (./prog)
[ ] Before adding the path to the cmd->cmd_paths check if we can run it with access.
[ ] Have an exit function that also frees our memory 
[ ] Bij iedere split in de envp meteen met access checken
[ ] ft_split handle commands in quotes ex. (grep "text text") also handle awk n stuff
[ ] in child_create if execve cant find 
[ ] also when we want to run files, totatlly ignore the path


## How to handle certain commands

### bash: cmd: command not found
"cmd arg1"
cmd


### bash: ./cmd: No such file or directory
#### also when we want to run files, totatlly ignore the path
/path/to/cmd
"/path/to/cmd arg1"

./path/to/cmd
"./path/to/cmd arg1"

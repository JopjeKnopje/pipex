# Pipex
## 42 Pipex project

Simulating the shell's pipe operator


## Resources
* https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY


## Notes
* Local executables are not required to be handled.


## TODO
[ ] Have an exit function that also frees our memory 
[ ] ft_split handle commands in quotes ex. (grep "text text") also handle awk n stuff
[ ] in child_create if execve cant find 
[x] also when we want to run files, totatlly ignore the path
[ ] run all the processes paralell, and only wait in the parent when you are done with spawning processes
[ ] pipex exitcode should be that of the last process


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

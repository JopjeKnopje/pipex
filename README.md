# Pipex
## 42 Pipex project

Simulating the shell's pipe operator


## Resources
* https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY


## Notes
* Local executables are not required to be handled.


## TODO
[ ] Have an exit function that also frees our memory 
[ ] run all the processes paralell, and only wait in the parent when you are done with spawning processes
[ ] pipex exitcode should be that of the last process
[ ] if we the program we execve segfaults we can detect it,
but if we segfault before the execve in the child. our entire program segvs (lag aan debug flags oeleh)

## Exit codes
* If the commands are runnable, always return the exitcode of the last process.
Een if one of the commands before it crashes or segfaults. (that is how bash handles it)

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

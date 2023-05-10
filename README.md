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
[ ] Error handleing in main is done

## Error handling
TODO Exit function that checks if its a bash error, or pipex error using a boolean,
and takes a string as message pipex ptr and boolean

## Split on abolute path
when running /usr/bin/head -1


Maybe handle "cmd1 arg 'arg2 arg3'"

## Segfault

When you run `./test_exec 0 | ./test_exec seg` it says "Segmentation fault (core dumped)" 
with exit code 139.
Do we also need to print the Segfault message?


## Sleep
when running this command we wait on the sleep and totatlly ignore the segfault 
./test_exec seg | sleep 5

Same here except we now return the segfault
sleep 5 | ./test_exec seg

## Exit codes
* If the commands are runnable, always return the exitcode of the last process.
even if one of the commands before it crashes or segfaults. (that is how bash handles it)

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

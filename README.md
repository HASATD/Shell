# BASIC shell

### main.c 
- This file is the main file for the execution of the shell. we also tokenize our commands wrt ";" in this file.

### ls.c
- This file contains the implementation of the ***ls*** command used to get the contents of a directory.some flags like -l,-a,-al are also implemented here.
  
### cd.c 
- This file contains the implementation of the ***cd*** command which is used to change directories in linux.

### echo.c
- This contains ***echo*** command which is used to print text on the shell.

### pwd.c
- This contains the implementation of the pwd command which is used to get the current working directory.
  
### pinfo.c
- This contains the implementation of pinfo command which prints the process-related info of the shell program. 

### prompt.c
- This contains the implementation of what's displayed on the shell.

### linked_list.c 
- This contains implementation of some operations based on linked lists.
  
### foreback.c
- This file contains the implementation for the execution of foreground and background processes.

### impl.c
- This file handles the execution of all the commands.This also tokenizes the commands wrt spaces.

### bgrndtest.c
- This file contains the implementation to check for a stopped background process and print its pid if the process is suspended.
  
### redirection.c
- This file contains the implementations of the symbols **>**,**<** and **>>**.

### pipes.c
- This file contains the implementation of the symbol **|** (pipe).

### signals.c 
- This file contains the implementation of ctrl-c and ctrl-z.

### sig.c
- This file contains the implementation of the command sig(sig Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to signal number to that process. The shell should
throw an error if no job with the given number exists.)

### jobs.c 
- This file contains the implementation of the command jobs which displays all the background processes.


# SIMPLE SHELL PROJECT

This is the first attempt from the three of us to make a project as a team and we had to recode a simple shell for the Holbertonschool.
The school project consisted in writing a shell like sh (Bourne Shell) by Stephen Bourne , in C, using a limited number of standard library functions.


## Usage

In order to run this program,
Clone This Repo
git clone https://github.com/Mikalach/holbertonschool-simple_shell

You will compile the program that way
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## How to use it

In order to use this shell, in a terminal, first run the program:\
prompt$ ./hsh\
It wil then display a simple prompt and wait for commands.\
$\
A command will be of the type\
$ {_your_command_}

## Example

This is an exemple\
$ ./hsh\
($) /bin/ls _// you can also write the path manually_\
($)\
($) exit\
$

or

This is an exemple\
$ ./hsh\
($) ls -la\
($)_*result of the command will be there_\*\
($) exit\
$


# Let's get started

One very basic command is echo. This command just prints text to the terminal. Try the command:

echo Hello, World
Then press enter. You should see the text "Hello, World" printed back to you. The echo command is useful for printing from a shell script, for displaying variables, and for generating known values to pass to other programs.

## List of authorized functions

access (man 2 access)\
chdir (man 2 chdir)\
close (man 2 close)\
closedir (man 3 closedir)\
execve (man 2 execve)\
exit (man 3 exit)\
_exit (man 2 _exit)\
fflush (man 3 fflush)\
fork (man 2 fork)\
free (man 3 free)\
getcwd (man 3 getcwd)\
getline (man 3 getline)\
getpid (man 2 getpid)\
isatty (man 3 isatty)\
kill (man 2 kill)\
malloc (man 3 malloc)\
open (man 2 open)\
opendir (man 3 opendir)\
perror (man 3 perror)\
read (man 2 read)\
readdir (man 3 readdir)\
signal (man 2 signal)\
stat (__xstat) (man 2 stat)\
lstat (__lxstat) (man 2 lstat)\
fstat (__fxstat) (man 2 fstat)\
strtok (man 3 strtok)\
wait (man 2 wait)\
waitpid (man 2 waitpid)\
wait3 (man 2 wait3)\
wait4 (man 2 wait4)\
write (man 2 write)\



## Authors

__Deboch Natnael__      https://github.com/Natnael04 \
https://www.linkedin.com/in/natnael-deboch-149642250/
__Djetic Mickael__      https://github.com/Mikalach \
https://www.linkedin.com/in/mickael-djetic-73b20523b/ \
__Guerin Alexandre__    https://github.com/AlexandreGRN \
https://www.linkedin.com/in/alexandre-gu%C3%A9rin-7b0825252/ \


## Special thanks

Special thanks to our moms who worked hard for us to be here.\
We would like to thank the staff and our wonderful peers at Holberton School for providing an effective learning experience throughout this project.
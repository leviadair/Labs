=============
MEMBERS
=============

Dale Hartman
PJ Onusconich
Stefano Cobelli
Levi Adair

=============
FEATURES
=============

Dale Hartman -

The added feature is a very basic implementation of Bash's alias feature.
During a run of the shell, simply type:
> alias [name of alias] [command to reference]
The command to reference must conform to the limitations of the shell's 
parsing (must not contain spaces).
example run:
> alias list ls
> list .

Stefano Cobelli -

Changing directory. entering "cd" followed by a path will change the current 
directory to the specified directory.
>gshell cd ..
>gshell cd .
>gshell cd ~/csci315
>gshell cd .././../../.

PJ Onusconich -

Re-running previous command entered. Typing "!!" at the prompt will execute the most recent command entered.
>gshell ls -lsa
>gshell !! (will execute "ls -lsa") 


Levi Adair- 
Implemented simple calculator 
works with operators of +,-,/,*,%,^ on integers with spaces in between everything

gshell> 1 + 2
gshell>answer is 3.000000 
gshell> 5 * 8
gshell>answer is 40.000000 
gshell> 7 / 2
gshell>answer is 3.500000 
gshell> 7 % 5
gshell>answer is 1.000000 

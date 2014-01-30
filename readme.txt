-------------------------
Jeremy Ni's hw1, CMPT300
SFU_ID: 301239927
SFU_EMAIL:zni@sfu.ca
2014.1.29
-------------------------

-------------------------
How to compile
-------------------------
Put "answer.c" in your working directory, open Terminal and run command "gcc answer.c".  You shall get an exetuiable file "a.out".  Run command "./a.out" and "Jeremy's Shell" should run in your terminal.

You will see something like this when the program is running successfully:
-------------------------
eg:
Wed Jan 29 20:02:05 2014
Jeremy's Shell:~/home$
-------------------------

-------------------------
Features included
-------------------------
1. Jeremy's Shell will show a prompt includes current time and working directory.

2. Three build-in commands were implemented:
	2.1 ls
		you can type command "ls" and Jeremy's Shell will list all the files in your current working directory in alphabet order.  Arguments are not allowed, eg:"ls -l".
	2.2 pwd
		when you type command "pwd" eremy's Shell will print your current working directory.
	2.3 cd
		2.3.1	
			command "cd", "cd " anf "cd ~" will change your working directory to your home directory.
		2.3.2   
			command "cd absolute-path" will change your working directory to the absolute-path.
		2.3.3 	
			command "cd folder" will look for the folder in your current directory and change the working directory into that folder.  If there is no such folder, Jeremy's Shell will output "No such file or directory!".

3. If you want to quit Jeremy's Shell, simply type command "exit".

4. All other shell commands are implemented using System Call "execvp".  If you type something other than a command, Jeremy's Shell will output something like "No command "xxxxx" found!".

5. All commands below has been tested succefully by the author:
(using Linux in CISL and OSX 10.9)
"cd","ls","pwd","cat ./readme.txt","vim readme.txt","xyz"(which doesnot exist and brins an error output),"ps".

6. Please give me full mark :) Thx!
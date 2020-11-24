                                        README OF TrinadhShell

HOW TO RUN THE CODE:

#   For compiling my code we need to run 'make' in the terminal. This will compile all the files which I created in creating my shell :)
#   Once you compile the code you will have ./a.out executable in the same folder. So you just need to run that executable.

> make
> ./a.out
<username@system_name:~>
    ........The commands you want to execute.......

#   For terminating from this shell you need to use ctrl D or type quit.

What Corresponds to What??

#   I/O redirection functionality is exclusively implemented in a file redirection.c which takes care of storing the current stdin and stdout and also the restoring them. redirection.c also contains fuction int redirectionfinder(char ** argument); which finds if there is a need to change the streams and changes them accordingly.

#   This verification and changing streams functions are called in command.c file which will pass the current command which is result of speration filters ; @ $ |. In this file we further give control to various individual commands and pass them to their respective files.

#   Pipes are implemented in pipe.c in which the command after the filters ; and @ $ is passed. This will makesure that the streams are changed accordingly and the flow of the code is correct.

#   We pass the resultant smaller commands from pipe to command.c file which will makesure that I/O redirection is stronger than pipe.

#   setenv command is implemented in command.c file as there is not much code to write. And the unsetenv is also implemented in command.c

#   jobs is implemented in command.c which just uses the linked list we used when implementing background process.

#   getjob is also implemented in command.c but we used function like isitnumber(char* string); which is implemented in isitnumber.c and we also used pidjob.c file which has function getmepid(int number);verifies whether it is  a valid pid or not.

#   bg is also there in command.c and uses similar functions from isitnjumber.c and pidjob.c to check whehter it is a number and whether the given number id pid or not. fg is also implemented similarly but uses one additional function getmestringofpid(char* argpass,int jobnumber); from pidjob.c

#   The entire logic of overkill command resides in overkill.c which will kill all the background processes which are still there.

#   quit and ctrl D their logic is there in main.c which will exit thee loop as they see either of them immediately.

#   ctrl Z functionality main code is there in corefg function in foreground which will add the currently converted to background process apart from that we also have few ignore and default dignal commands used fot this purpose in main.c foreground.c background.c

#   ctrl C fuctionlity is placed in main.c which signal ignore statement and in foreground child where we restore to default.

#   cd - functionality is added into the cd.c previoulsy used. Exitcodes verification is done at prompt.c . And and Or commands logic is explicitly placed in andor.c which will parse the string accordingly and will pass it to pipeit function.

#   One of the main change it that in this assignment we placed all the repedly used code in global.c code which includes struct node * head ; and the copies of the stdin and stdout and insertion into the list functionality is also added into the global.c and the signal handler is also migrated here.

From here on the codes which are implemented as part of assignment 2 are explained:

#   main.c this is the file in which the basic infinite loop which will wait for input in the terminal. This file will take the input and passes it to the other files which require it.
#   prompt.c this file is responsible for the prompt which is visbile in the terminal. This will makesure that correct directory and username and syestem name are printed to terminal.
#   input.c  if more than one command is passed as an input then this will makesure that individual commands are seperated correctly and each one is processed one after the ohter.
#   command.c this file will call different files based on the input which is provided for example if the command is echo command then this will call echo implementing function similarly for other functions.
#   headers.h this is list of common libraries which are used in all files used in this assignment.
#   pwd.c this file will implement pwd command. 
#   echo.c this will implement echo command.
#   cd.c this will contain cd functionality.
#   ls.c this will contain ls functionality.
#   foreground.c will contain foreground implementation and its funtionality.
#   background.c will conatain background implementation.
#   pinfo.c will contain pinfo implementation.
#   history.txt is the file where my history is written to the disk
#   night.c contains the implementation of the nightswatch commands both interrupt and newborn
#   makefile this conatins the command to compile all the files together and create executable.
#   I made assumptions that the individual command is less than 150 bytes and the length of totla command is less than 2000bytes so please give commands which are within the limits.
#   And the code only runs for the flags which are given in the pdf and nothing else.
#   ls command makes an assumption that the memory of each file is less than 11 digits. The given argument should be a directory and nothing else.
#   The max commands allowed are only 24 in  a single command.
#   In nightswatch command there is small delay because of scanning the stream.
#   All assumptions which are allowed as said by TA are taken in to consideration while implementing.

FEATURES I ADDED:

#   If a same command is typed twice consectively then only once the command will be added to the history,txt For exaple if my commands are as follows:
>       history
>                       history
Even though the commands are not strictly same but if we remove the leading and terminating extra spaces then they are same. In that case the command will be added only once. This is implemented to resemble Bourne bash shell behaviour.
#   I tried to delete the characters that user types when I am printing each row in nightswatch > interrupt. This I added to makesure that because of the input given by the user the pattern shouldnot be disturbed. This is agin will enhance the user experience with my shell.
#   I added how the background process terminated rather that just saying that it terminated. My code will say if it is terminated normally or whether it is killed by a signal in which it will print that the process ended abnotmally.
#   I resembled the Bourne bash shell behaviour by printing [1] pid after a background process is created.
#   perror is printing in most of the cases which I felt an error might occur.


ASSUMPTIONS MADE:

#   Some commands like interrupts in nightwswatch is specific to kernal so the command will only work in kernal whose version is same which is 5.3.0-28-generic.
#   Length of commands which are given is less than 1000B and individual commands in a command is less than 150B.
#   Number of bytes in a file are less than 10pow11, this assumption is used while implementing ls, for printing number of bytes in  a file.
#   Echo is implemented as mentioned in moodle.
> echo trinadh's    "shell"     is good
....trinadh's "shell" is good
#   Argument given in ls command should be directory as mentioned in pdf for rest of the things this would not work.
#   Number of pipes which can be given in a single command are atmost 20. If exit code is not 0 then it is corresponds to unsucessful.
#   If the ctrl C is used then exit status corresponds to failure. Diff with difference corresponds to unsucessful exit and without difference corresponds to sucessful exit.
#   If mulitple redirections are done then the last input redirection file will be considered, same with output rediredction.
#   All the error messages are written to stderr, the output of cd - is stdout , and jobs to stdout. And all other outputs where the output is printed is written to stdout.

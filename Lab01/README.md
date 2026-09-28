# System Metrics & Characterization

## Goals of the Lab Session

- Set up the working environment.

- Learn basic system metrics.

- Obtain and report system metrics given a problem/exercise description.

- Obtain and report system metrics using profiling tools.

## Outline

- Lab Environment.

- Part I: Metrics Definitions.

- Part II: Written Exercise.

- Part III: Profiling Tools.

- Appendix A: Shell Basics.

- Appendix B: Compiler Basics.

- Appendix C: Debugger Basics.

## Lab Environment

Part III (and appendices) will be conducted remotely connecting through Secure Shell (ssh) to the educational server lab000.cps.unizar.es.

Conneting to all the educational servers (including lab000, hendrix, pilgor, etc.) can be done using your institutional credentials (e.g., username a123456 and your administrative password). Depending on your previous experience on these servers, you may consider the following:

- Those who have never used any of these servers before follow this [link](https://webdiis.unizar.es/cgi-bin/hendrix-pw) to create a new account.
  
- Those who have already an account but do not remember the password, or simply have never used these services, follow this [link](https://webdiis.unizar.es/cgi-bin/hendrix-newpw) to set up a new password.

- Those who would like to change the type of Shell for the remote machines at the university (bash Shell is more friendly) use this [link](https://webdiis.unizar.es/cgi-bin/hendrix-chsh).

The process to connect remotely to lab000 using ssh varies depending on the local Operating System (OS):

- UNIX/Linux: open a Shell terminal and run this command:

```
ssh -X a123456@lab000.cps.unizar.es
```
Where a123456 is your username and the option -X enables X11 forwarding (it allows graphical applications running on the remote machine to display their windows on your local machine).

- Windows: there exist many applications to perform the ssh connection such as PuTTY+Xming, MobaXTerm, etc. For example, refer to this [document](http://webdiis.unizar.es/asignaturas/PROG1/doc/anuncios/programar_en_hendrix_desde_casa.pdf) to configure PuTTY+Xming.

Finally, there are many text editors to code C/C++ programs such as vi or vim, which will allow us to write programs without the need for windows, or other windows-based editors like emacs or gedit (already installed in the server side). Choose your preferred option to navigate and edit code.

## Metrics Definitions

- Execution time: the time required by a computer to execute a given program or workload, from start to completion.

- Performance: the amount of useful work completed per unit of time. For a fixed workload, it is commonly defined as:

\[
\text{Performance} = \frac{1}{\text{Execution time}}
\]

- Clock cycles

- Clock rate (operating frequency)

- Cycle time

- Instructions count

- Cycles Per Instruction (CPI)

- Instructions Per Second (IPS)

- Data bandwidth (dBW)

- Instructions bandwidth (iBW)

- Floating-Point Operations (FLOP)

- FLOP per Second (FLOPS)

- Energy Per Instruction (EPI)

- Energy Per FLOP (EPF)

- Performance to power ratio (Computing efficiency)

## Appendix A: Shell Basics

A Shell or command line interpreter is a user interface that is navigated by typing commands at prompts (requests for input). Unlike a Graphical User Interface (GUI) OS, a Shell only uses a keyboard to navigate by entering commands and does not utilize a mouse for navigating. Although using a Shell requires to remember many different commands, it can be a valuable resource and should not be ignored. Using a Shell, you can perform almost all the same tasks that can be done with a GUI. However, many tasks can be performed quicker with powerful commands and can be easier to automate (through the execution of batch files or scripts) and do remotely.

Extended information and usage for every command can be obtained by typing: `man command_name`

The next subsections summarize basic commands about the management of files, directories, synchronous/asynchronous execution, standard input/output (I/O), processes, and so on.

### Autocomplete function

Autocomplete is a useful function to speed up the writing of a command line. Press TAB at any time while writing a command to experience the effect. If the function does not seem to work, type the command `set +u` and try again.

### Files (Namespace)

- Path of the current directory: `pwd`
- Change current directory to dirname: `cd dirname`
- Change to home directory: `cd`, `cd $HOME`
- Change to root directory: `cd /`
- Change to parent directory: `cd ..`
- Change to current directory: `cd .`
- Listing contents of a directory: `ls dirname` (empty dirname refers to the current directory)
- Absolute and relative paths

#### Examples (try each command as a sorted list and check out the effect of each of them. Alternatively, you can add other commands in between and check out their effects as well)

```
01. pwd
02. ls
03. cd / 
04. ls 
05. cd proc
06. ls
07. pwd
08. cd
09. pwd
10. cd ..
11. ls
12. cd /home/username/Desktop
13. pwd
14. cd /proc
15. cd ../home/username/Desktop
16. pwd
```
**Important notice:** In the case of using the guest account instead of yours, commands #12 and #15 should be replaced by `cd /export/home/guest/Desktop` and `cd ../export/home/guest/Desktop`, respectively.

Commands #12 and #15 refer to the same directory. The difference lies in that the former uses an absolute path from "/" to reach the directory destination (no matter what the current directory is), whereas the latter uses a relative path from the current directory (/proc) to reach the destination.

**Download the lab1_materials.tar.gz file from either Moodle or the GitHub code tab and copy it to your $HOME directory. Then, unzip the file using the command:**

```
$> tar -xzvf lab1_materials.tar.gz
```
Note that symbols `$>` refer to the prompt of the Shell and should not be included in the command-line order.

### Directories (Create, Remove, Listing)

- Creation of new directories: `mkdir`
- Removal of directories: `rmdir`
- Listing hidden files: `ls –a`
- Listing extended information: `ls –l`

#### Examples

```
01. cd
02. cd PACS
02. mkdir trash
03. mkdir dir1 dir2 dir3
04. ls -l
05. cd trash
06. pwd
07. cd ..
08. pwd
09. rmdir trash
10. ls dir1
11. ls –a
12. ls –a dir1
```

### Files (Copy, Move, Listing Contents)
	
- Copying files: `cp`
- Moving/changing name of files: `mv`
- Removal of files: `rm`
- Listing contents of files: `more`, `cat`
- Editing files: `vi`, `vim`, `emacs`, `gedit`, `nano` (and many others...)

#### Examples

```
01. cd
02. cp /home/username/PACS/lab1/HelloWorld.cpp . (using guest account: cp /export/home/guest/PACS/lab1/HelloWorld.cpp .)
03. ls
04. cp PACS/lab1/HelloWorld.cpp another.cpp
05. ls
06. mv another.cpp program.cpp
07. ls
08. mv program.cpp PACS/dir1
09. ls
10. cd PACS/dir1
11. ls
12. rm program.cpp
13. cd ..
14. rmdir dir1
15. ls
16. cp lab1/HelloWorld.cpp dir2
17. more lab1/HelloWorld.cpp
18. more dir2/HelloWorld.cpp
```

### Synchronous/Asynchronous Execution

Synchronous execution (step by step):

- Shell waits for a command.
- Shell launches the command to be executed.
- **Shell waits for the execution to finish.**
- Shell waits for a new command.

#### Example

```
$> gedit new.cpp
```

Asynchronous execution (step by step):

- Shell waits for a command.
- Shell launches the command to be executed.
- **Shell does not wait for the execution to finish and immediately waits for a new command that can be launched while the previous one is still running.**

#### Example

```
$> gedit new.cpp &
```

### Standard I/O

Every command/process launched by the Shell has three communication ways:

- Standard input: the process reads from the keyboard.
- Standard output: the process writes to the screen.
- Standard error output: the process writes error messages through an alternate way to the screen.

The above behavior can be changed from the Shell with alternate forwarding options as follows:

- prog > f: forwards the standard output of the prog command to the f file. The file is shorten if already exists and created if the file does not exist.
- prog >> f: forwards the standard output of the prog command to the f file, preserving the original content of f and adding the new content at the end of the file.
- prog < f: forwards the standard input to f. The file must exist.
- prog 2> f : forwards the standard error output to f. The file is shorten if already exists and created if the file does not exist.
- prog1 | prog2: forwards the standard output of prog1 to the standard input of prog2.

#### Examples

```
01. cd $HOME/PACS/lab1 
02. ls –l > trash
03. more trash
04. cat < trash
05. cat < trash > trash2
06. more trash2
07. cat < trash >> trash2
08. more trash2
09. cat < trash | wc
10. man wc
11. rm trash trash2
```

### Parameter Passing in C++

The main() routine of a C++ program can receive the following parameters: `argc` (argument count) and `argv` (argument vector).

```
int main (int argc, char *argv[]) { /* ... */ }
```

The Shell initializes these variables and they can be used later on by the program. The argc parameter contains the number of arguments (words) in the command line that launched the program, whereas argv is an array of character pointers listing all the arguments. For instance, for the following command line:

```
$> ./myprogram hey you 6
```
The Shell sets argc=4, argv[0]="myprogram" (i.e., the name of the program), argv[1]="hey", argv[2]="you", and argv[3]="6". Note that argv[3] is a char, not an integer.

### Processes (Information and Removal)

- Information about processes: `ps`
- Information about user processes: `ps –u username`
- Extended information about user processes: `ps –lu username`
- Remove/killing a process: `kill -9 PID`, where PID refers to the process id, and can be retrieved from the output of the above command
		
#### Examples

```
01. ps
02. ps –u username
03. ps –lu username
04. man ps
05. kill -9 PID
```

Finally, you are encouraged to check out these games from [OverTheWire](https://overthewire.org/wargames/bandit/) and [MIT](https://web.mit.edu/mprat/Public/web/Terminus/Web/main.html) to learn more command line skills.


# System Metrics & Characterization

## Goals of the Lab Session

- Set up the working environment.

- Learn basic system metrics.

- Obtain and report system metrics given a problem/exercise description.

- Obtain and report system metrics using profiling tools.

## Outline

- Lab Environment.

- Part I: Metrics Definitions.

- Part II: Written Exercise (includes deliverable).

- Part III: Profiling Tools (includes deliverable).

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

$$
\text{Performance} = \frac{1}{\text{Execution time}}
$$

- Clock rate (operating frequency): the number of clock cycles generated per second, measured in Hz. For example, 2.5 GHz = 2.5 × 10⁹ cycles/s.

- Cycle time: the duration of one clock cycle. It is the inverse of the clock rate:

$$
\text{Cycle time} = \frac{1}{\text{Clock rate}}
$$

- Clock cycles: the number of processor clock periods required to execute a workload:

$$
\text{Clock cycles} = \frac{\text{Execution time}}{\text{Cycle time}}
$$

- Instructions count (IC): the total number of machine-level instructions executed by a program/workload.

- Cycles Per Instruction (CPI): the average number of clock cycles required to execute one instruction:

$$
\text{CPI} = \frac{\text{Clock cycles}}{\text{IC}}
$$

- Instructions Per Second (IPS): the number of instructions executed per second:

$$
\text{IPS} = \frac{\text{IC}}{\text{Execution time}} = \frac{\text{Clock rate}}{\text{CPI}} 
$$  

- Data bandwidth (dBW): the rate at which data are transferred or processed, typically measured in bytes/s or bits/s. The precise definition depends on the system and workload. In this course, we will assume:

$$
\text{dBW} = \frac{\text{OC} \times \frac{\text{bytes}}{\text{operand}}}{\text{Execution time}}
$$ 

Where OC is the Operands Count measured as the number of memory (load and store) instructions of a program, assuming a given memory instruction transferes a single operand.

- Instructions bandwidth (iBW): the rate at which instructions are transferred, typically measured in instructions/s.

$$
\text{iBW} = \frac{\text{IC} \times \frac{\text{bytes}}{\text{instruction}}}{\text{Execution time}}
$$   

- Floating-Point Operations (FLOP): the number of individual floating-point arithmetic operations performed by a workload, e.g., additions and multiplications. FLOP is an operation count, not a rate.

- FLOP per Second (FLOPS): the rate at which floating-point operations are performed:

$$
\text{FLOPS} = \frac{\text{FLOP}}{\text{Execution time}}
$$

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

## Appendix B: Compiler Basics

Compilation tools help the programmer in the process of generating the binary (machine code) corresponding to the program to be implemented. When we think of compilation tools we should not limit ourselves to the compiler alone. We must add to the list debuggers and program behavior analyzers (performance, code, memory, parallelism...). These tools help the programmer to obtain a correct, safe, and efficient binary.

The compiler is a tool capable of translating a program written in high level (C, C ++, Ada, Pascal...) to machine or binary code that can be executed on the target processor (x86, x64, SPARC V9...).

Once the program of the application that we want to implement has been coded in a high-level language, we save it in a text file, which we will call a source file. The generation of a binary (executable file) from a source file in a high-level language requires two compilation phases: translation (transfer) and linking (link). In the first phase, the compiler analyzes the source file in high-level language and generates an equivalent program in native machine language of the processor architecture in which we want to execute the program. As a result, the translation phase generates an object file. To finish building a binary file of the complete program, all those functions and procedures that are used but whose implementation can be found in other object files (system library or user library) are required. In the linking phase, the objects (or a reference to them) containing the external functions and procedures (system or user) used by the original source are added.

The programs that we write in C++ language must be stored in a simple text file whose extension will be ".cpp". The default extension of the object files will be ".o". In the lab machines, we have the GNU g++ compiler for programs written in C++ language. This tool does the compilation phases, translation and linking, in a joint or separate manner.

To perform only the translation, use the `–c` flag:

```
$> g++ -Wall -c sourcecode.cpp
```
The `-Wall` flag enables all the warning messages from the compiler during the compilation process. It is encouraged to include such a flag in all compilations. On a successful translation, a sourcecode.o file is produced as a result. This file refers to the object file of the source file sourcecode.cpp. Try such a command with the HelloWorld.cpp example.

If we want to carry out the linking of several object files to generate the executable (named "binary_file" in the command below), we must use the `-o` flag. Only one of the object files must have the main symbol defined, which will be the entry point to the program. Those objects belonging to system libraries do not need to be specified as they are automatically added by the compiler:

```
$> g++ -Wall object0.o object1.o object2.o ... objectN-1.o -o binary_file
```

Try the above command using the HelloWorld2.cpp and func.cpp source files. Remember that the corresponding object files should be generated first.

Finally, if we want to generate the executable file corresponding to the source file in a single step, use the `–o` flag:

```
$> g++ -Wall source0.cpp source1.cpp ... sourceN-1.cpp -o binary_file
```

If the `-o` flag is not specified, an executable named "a.out" will be generated by default. Furthermore, this command allows specifying object files as input to the compilation tool.

With the `-v` flag specified in the compilation command, verbose information on all the steps the tool takes while compiling a source file is displayed. In addition to these options, compilers have many other available options. Type the following command for further information:

```
$> man g++
```

Once the executable file of our program has been generated, we can launch it from the command line itself using:

```
$> ./binary_file
```

**Food for thought: why could be of interest to separate the translation and linking phases during compilation?**

## Appendix C: Debugger Basics

A debugger is an application for finding out how a program runs or for analyzing the moment a program crashes. Debuggers usually perform many useful tasks, including running the program, stopping the program under specific conditions, analyzing the situation, making modifications, and testing new changes.

GDB can be used as a C++ debugger if a program is compiled with the GNU g++ compiler and the `–g` flag is enabled. By debugging with GDB, you can detect errors and solve them before they cause severe issues. The first step of learning how to use GDB for C++ debugging is to compile the C++ code with the `-g` flag:

```
$> g++ -Wall -g sourcecode.cpp –o binary_file
```

The next step is calling GDB to start the debugging process for the program you wish to analyze:

```
$> gdb binary_file
```

Try the above command using the binary after compiling mult.cpp. The above command opens GDB but does not run the program. There are several ways of running the opened program. First, the program can be executed with the run command:

```
(gdb) run
```

Command-line arguments can be passed if the program needs them:

```
(gdb) run arg1 arg2 ... argN-1
```

A program can be debugged more efficiently using breakpoints. Breakpoints refer to instructions that stop the execution at specific code locations. For instance, breakpoints can be set in places suspected to be problematic. It is a common practice to set breakpoints before running the program. Breakpoints can be set in two ways:

- Setting a line at which the execution stops.
- Setting a function name to stop the execution at.

The following example sets a breakpoint at the start of the main function:

```
(gdb) b main
```

This example sets a breakpoint at a specific line (7):

```
$ (gdb) b 7
```

This example lists all of the breakpoints:

```
$ (gdb) info b
```

This command deletes the breakpoint at line 7:

```
$ (gdb) delete 2
```

You might need to execute a program slowly, moving from one line to the next one. There are two ways of making the program run step-by-step.
The command next, or simply n, executes the current command, stops, and displays the next line for execution. However, if the line is a function call, the debugger will fully execute the function before the execution stops again:

```
$ (gdb) n
```

To execute line after line, even if a new function is invoked so that the sequential program flow breaks, the command step (s) can be used.

The command continue (c) resumes the execution until the end or the next breakpoint:

```
$ (gdb) c
```

The values of variables can be checked during specific moments of the execution. The print command can be used for this task. It is possible to print more complicated expressions, type casts, call functions, etc.

Syntax for using print:

- print \<exp\>: to get values of expressions.
- print /x \<exp\>: to get the value of expressions in hexadecimal.
- print /t \<exp\>: to get the value of expressions in binary.
- print /d \<exp\>: to get the value of expressions as unsigned int format.
- print /c \<exp\>: to get the value of expressions as signed int format.

Use combinations of the above commands to show how the variables i, j, and v are updated after a few iterations of the innermost loop of mult.cpp.

More commands and further details can be seen typing:

```
(gdb) help
```	

The command quit (q) allows to exit from the gdb environment.



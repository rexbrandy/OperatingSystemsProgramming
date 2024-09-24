# Practical Case Study B Operating Systems Programming – COMP 3015

### 1 Introduction
A Shell or Command Language Interpreter (CLI) is a piece of software that provides a simple, but powerful, textual interface for users to an operating system. In this Case Study you will investigate the operation of and implement a simple CLI.

### 2 Specification
A CLI accepts textual input from the user, and executes the commands issued. The main logic of the CLI is given in pseudocode below:
```
main: loop
    get input line
    if end of input exit
    break line into words
    command := first word of line
    found := false
    if command is builtin
    then
      do_builtin(line)
      found := true
    else
      found := find_and_execute(line)
    end if
    if not found report error
  end loop
```


Your first task will be to write a program that repeatedly reads a line of input from the user, the fgets() function (see Sect. 4 for usage information of all system provided functions) will help you here. Your program should end when either end of the input file is encountered, or the exact word exit appears in the input as the only word on a line. Traditionally both the File System and Command Language are case sensitive, you should also implement this.

Your next task will be to break the line up into words, which are separated by one or more spaces. The provided function tokenize() does this, and it uses strtok() internally. You may use this function if you wish, in which case you should provide documentation on its operation, or you may write your own parser.

You should next implement the find_and_execute() section of the logic above, by creating a new process using fork(), and then use one of the exec() f amily of functions to run the program requested by the user in the text provided. If the requested program

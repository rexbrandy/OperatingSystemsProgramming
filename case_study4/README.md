# Case Study 4 Operating Systems Programming

## 1 Introduction
In this workshop you will investigate file I/O and file copy operations.


## 2 Specification
Following on from the demonstration program cp1.c presented in the lecture, we will make a series of modifi- cations to the program.
Firstly, what happens when the cp1.c program is asked to copy a file onto itself, i.e. cp1 input input? Is this what you expect? Modify the program to do something more sensible! As a hint, two files are the same if they are on the same device and have the same i-node number (which stat() can give you), simply comparing the names is not enough.

Secondly, a real copy program will assign the same file permissions to the destination as were on the source, modify your answer to the last part to do this.

Thirdly, real copy programs allow the second argument to be a directory, i.e. you specify a directory for the second part and a copy of the source is placed in that directory with the same name as the source. Modify the answer to the last part to include this functionality. You should allocate the space for the new name dynamically.

Fourthly, your program should rename the original version of the destination file to filename.bak (i.e. add an additional extension of .bak) if the destination file exists, or if the destination is a directory that a file with the same name exists in the directory.

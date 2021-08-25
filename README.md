A CLI utility which performs a byte by byte checking between the contents of two files.

[INSTRUCTIONS]
[COMPILING] => gcc main.c -o main
[RUNNING] => ./main file1.txt file2.txt

There is the fsize option that you can use to specify how much bytes you want to compare.

If you want to use this option you have to run the program as follow:

./main file1.txt file2.txt 3

In this case only the first 3 bytes will be used as comparison between the two files.

# Advanced

When you get the hang of it, you can use the terminal to perform a range of tasks very efficiently. On this page we collect a series of examples of slightly more advanced terminal usage. 

**Preparation**: For many of the examples it will be useful to have a test directory with a number of dummy text files. Here is set of commands that will create a directory called `example_advanced`, enter it, populate it with ten empty files (`file_1.txt`, ..., `file_10.txt`), and finally write three lines of text to each file:

```sh
mkdir example_advanced
cd example_advanced
for i in {1..10} ; do touch file_${i}.txt ; done
for f in file_*.txt ; do for i in {1..3} ; do echo "This is line ${i} of ${f}" >> ${f} ; done ; done
```
Don't worry if these commands don't make much sense yet --- they will by the time you've read through this page. For now, let's just confirm that these commands did what we intended by looking at the content of one of the files:

```sh
less file_5.txt
```
This should give you a screen showing you the content of `file_5.txt`:
```
Line 1 in file_5.txt
Line 2 in file_5.txt
Line 3 in file_5.txt
```
You can exit the `less` command by pressing 'q'.


## Run multiple commands in sequence

You can run multiple commands in one go by using a semicolon to separate the commands:

```sh
echo "command one" ; echo "command two" ; echo "command three"
```

If you only want to run the next command *if* the previous command completed successfully, you can use `&&` as separator. So in this next example, the last command will *not* be run:

```sh
echo "command one" && I-made-a-typo-here && echo "command three"
```

## Passing output




<!--

ctrl-shift-c
ctrl-shift-v

ctrl-r 

multiple commands on one line

man COMMAND
COMMAND help
ssh
grep
piping
sending output to file
appending to file
loops
head / tail
2>&1 | tee 
-->




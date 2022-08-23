# Basics 
*or: How I Learned to Stop Worrying and Love the Terminal*

On this page you will learn some basics (and some not-so-basics) of working from the **terminal**, a.k.a. the **shell**, a.k.a. the **command line**, a.k.a. the **console**. Typing commands instead of the usual point-and-click may feel a bit clumsy and old-fashioned at first. But if you stick with it, you'll soon realize why the terminal is a standard tool for code developers, computational scientists and anyone else doing fancy stuff with computers.

For the examples below we will often need some dummy directories and files. To create/download these files and directories we'll provide one-line *preparation commands* that you can simply copy and paste into the terminal. To paste in the terminal, right-click or press **ctrl-shift-v** (Linux) or **cmd-c** (MacOS). To execute a command, simply hit 'enter'. 

Don't worry if you don't yet understand what's going on in these preparation commands --- you'll learn all of it soon. After each example we also provide a single-line command that deletes the dummy files we've just created.

We will start by creating a directory `compphys_examples` in our home directory and go to that directory. This directory will be starting point for the examples below.

```sh
mkdir $HOME/compphys_examples && mkdir $HOME/compphys_examples ; cd $HOME/compphys_examples && echo "" && echo "current directory: $(pwd)" && echo ""
```

```{note}
Don't miss the [keyboard shortcuts](sec:keyboard_shortcuts) --- they will make your life in the terminal much easier.
```


## Navigation 

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir navigate && cd navigate && mkdir emptydir dirA dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

The basic commands for finding your way around the system are `pwd`, `ls` and `cd`:

```sh
# Print the directory you're currently in (the 'working directory')
pwd

# List directory content
ls           # List content of the current directory
ls dirA      # List content of the directory 'dirA' 
ls -l        # A more detailed content list, with time stamps, file sizes, etc.
ls -lh       # Same as above, but with file sizes given in 'human readable' units

# Change directory
cd dirA                 # Move into directory 'dirA'
cd ..                   # Move back up one directory
cd dirA/dirB            # Move into directory 'dirA/dirB'
cd ../../               # Move up two directories
cd                      # Move directly to the home directory (typically /home/yourusername/)
cd ~                    # Same as above
cd $HOME                # Same as above 
cd /home/yourusername/compphys_examples  # Move to a directory using its full ('absolute') path
```
**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r navigate
```

## Get help

Before going further it's useful to know how to get help. All the standard terminal commands come with a `--help` option. This will typically show you a summary of how to use the command and the different options that exist. For a more complete documentation, use the *manual* command `man`. Here are two examples using the `pwd` command:

```sh
pwd --help   # Print the help screen for the pwd command
man pwd      # Display the manual for the pwd command. Exit by pressing 'q'.
```


## Copying, moving and renaming files and directories

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir copy_move_rename && cd copy_move_rename && mkdir emptydir dirA dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

The basic command for copying is `cp`, and the command for moving and renaming is `mv`. 

```sh
# If you get confused, use the 'pwd' and 'ls' commands to
# see where you are and what files/directories are present

# Copy files
cp file1.txt file1_copy.txt          # Make a copy of file1.txt in the current directory
cp file1.txt dirA/file1_copy.txt     # Make a second copy and place it in dirA

# Copy directories
cp -r dirA dirA_copy                 # Note the -r ('recursive') flag for copying directories

# Move files
mv file1.txt dirA/                   # Move file1.txt into the directory dirA

# Rename files and directories
mv file1_copy.txt file1_renamed.txt  # Rename file1_copy.txt to file1_renamed.txt
mv dirA_copy dirA_renamed            # Rename the directory dirA_copy to dirA_renamed
```
**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r copy_move_rename
```


## Deleting files and directories

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir delete && cd delete && mkdir emptydir dirA dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

The basic command for deleting stuff is `rm` (for *remove*). To remove an empty directory you can use `rmdir`.

```sh
rm file1.txt                            # Delete the file file1.txt
rm dirA/file2.txt dirA/dirB/file3.txt   # Delete the two files dirA/file2.txt and dirA/dirB/file3.txt
rm -r dirA                              # Delete the entire directory dirA with all content (note the -r flag)
rmdir emptydir                          # Delete the empty directory emptydir
```

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r delete
```

```{note}
*With great power comes great responsibility!* If you delete or overwrite a file/directory by mistake, it is basically gone. (Unless it's a file that is tracked by `git` --- then it's very easy to restore it. You will learn about that in the git section.) So it can be wise to take a second look before executing a `rm` or `mv` command. For instance, you *never ever* want to do the mistake of accidentally running the command `rm -r /`, which would delete *everything* your user has access to. Another dangerous example is `rm -r *`, which would delete everything in the current directory and all subdirectories --- so you want to make very sure you're in the correct directory... (See below for an explanation of the wildcard `*`.) 
```

(sec:wildcards)=
## Using wildcards

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir wildcards && cd wildcards && mkdir dirA && touch file1.txt file2.txt file3.txt file11.txt file12.txt file13.txt dirA/file.txt dirA/bare.skrot dirA/tull.ball && echo "" && echo "current directory: $(pwd)" && echo ""
```

The wildcards `*`, `?` and `[]` allow you to perform commands on groups of files/directories. Wildcards can be used with all terminal commands. Here are some examples using the `ls`, `rm` and `mv` commands:

```sh
ls file*             # List files with names beginning with "file"
ls *.txt             # List files with names ending with ".txt"
ls f*.txt            # List files with names beginning with "f" and ending with ".txt"
ls file?.txt         # List files that match "file?.txt" where "?" can be any single character
ls file[123].txt     # List files named "file1.txt", "file2.txt" or "file3.txt"

rm dirA/*.txt        # Delete files in directory dirA with names ending with ".txt"
rm dirA/*            # Delete all files in dirA

mv *.txt dirA/       # Move files ending with ".txt" into the dirA directory
```

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r wildcards
```


## Viewing files

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir view_files && cd view_files && echo "Line number 1" > file1.txt && echo "Line number 2" >> file1.txt && echo "Line number 3" >> file1.txt && echo "Line number 4" >> file1.txt && echo "Line number 5" >> file1.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

There are several commands for inspecting the content of files directly from the terminal. Below we demonstrate the commands `cat`, `head`, `tail` and `less`. (For a more in-depth explanation, see [here](https://i.redd.it/jlaxkglh1iw41.png).) We also demonstrate how to use the `wc` command to count the number of words or lines in a file.

```sh
cat file1.txt        # Print the full content of file1.txt to the terminal screen
head -3 file1.txt    # Print the first 3 lines of file1.txt
tail -2 file1.txt    # Print the last 2 lines of file1.txt
less file1.txt       # View file1.txt interactively. Press 'q' to return to the terminal

wc -w file1.txt      # Count the number of words in file1.txt
wc -l file1.txt      # Count the number of lines in file1.txt
```

```{note}
Viewing files like this only works for text-based (i.e. human readable) files. For files in some binary format, e.g. a compiled C++ program, you won't get sensible output from commands like `cat` and `less`. (Try it and see.)
```

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r view_files
```



## Download files

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir download_files && cd download_files && echo "" && echo "current directory: $(pwd)" && echo ""
```

If you have the URL you can download a file directly from the terminal with the `wget` command. Let's demonstrate it by downloading the markdown (`.md`) file that this page is built from:

```sh
wget https://raw.githubusercontent.com/anderkve/FYS3150/master/book/using_the_terminal/basics.md

less basics.md   # Take a look at the downloaded file
```

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r download_files
```


## Run programs and scripts

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir run_programs run_programs/dirA && cd run_programs && echo "echo \"This program does nothing\" " > some_script.sh  && echo "echo \"This program also does nothing\" " > dirA/some_other_script.sh  && chmod u+x some_script.sh dirA/some_other_script.sh && echo "" &&  echo "current directory: $(pwd)" && echo ""
```

To run an **executable** (a compiled C++ program, a shell script, etc.) we simply specify the path to the executable file and hit 'enter'. When the file lives in the current directory, we specify the directory with `./`:

```sh
./some_script.sh             # Run some_script.sh that lives in the current directory
dirA/some_other_script.sh    # Run some_other_script.sh that lives in the directory dirA
./dirA/some_other_script.sh  # Same as above
$HOME/compphys_examples/run_programs/some_script.sh   # Run a script using its full (absolute) path
```

If you write your own script, the file will not automatically be executable. You first have to change the **file mode** using the `chmod` command. Let's quickly demonstrate this using the `some_script.sh` script:


```sh
chmod a-x some_script.sh   # Remove the execution ('x') mode for *all* users ('a')
./some_script.sh           # This will now fail with a "permission denied" error
chmod u+x some_script.sh   # Add the execution mode only for the *owner* ('u'), which is you
./some_script.sh           # This will now work again
```

More generally, the `chmod` command is used to set who should have has permission to read from, write to and/or execute a file. You can see which permissions are set for a file by listing it with the `ls -l` command and read the string of `r`, `w`, and `x` characters at the beginning of the output. If e.g. the command 

```sh
ls -l some_script.sh
```
outputs 

```
-rwxrw-r-- 1 youruser youruser 34 aug.  20 17:00 some_script.sh
```

the first three characters (`rwx`) after the first dash (`-`) say that the **owner** has read, write and execute permissions, the next three characters (`rw-`) show that users in the same **group** as the owner have read and write permissions, and the final three characters (`r--`) say that **others** only have read permission.


**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r run_programs
```


## Write terminal output to file

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir write_to_file && cd write_to_file && echo "echo \"0.1423e+2  0.7123e+1  0.9423e+0  -0.8720e+1\" " > some_script.sh && chmod u+x some_script.sh && echo "" &&  echo "current directory: $(pwd)" && echo ""
```

The output from a command can be written to a file by using the `>` operator. This will *overwrite* any existing content in the output file. To *append* to an existing file, use the `>>` operator:

```sh
./some_script.sh   # Run some_script.sh. This just prints some dummy data to screen

./some_script.sh > myoutput.txt   # Run some_script.sh and save the output in the file myoutput.txt
cat myoutput.txt                  # Check the content of myoutput.txt

./some_script.sh > myoutput.txt   # Run some_script.sh again. This *overwrites* the previous myoutput.txt
./some_script.sh >> myoutput.txt  # Run some_script.sh again, but *append* to the end of myoutput.txt.
cat myoutput.txt                  # myoutput.txt should now contain two lines
```

It is often useful to *both* see the terminal output directly on screen *and* save it to a file. This can be achieved by combining the original command with the `tee` command, using the **pipe** operator `|`. You will learn more about this in the [piping](sec:piping) section below, but for now here's a useful example:

```sh
# Run some_script.sh. The output will be displayed 
# on screen *and* saved to some_script_output.txt. 
# The funny-looking "2>&1" ensures that any potential 
# error messages (technically: output to STDERR) will 
# also be saved to file.
./some_script.sh 2>&1 | tee some_script_output.txt

# Print the content of some_script_output.txt
cat some_script_output.txt
```


**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r write_to_file
```


## Search for files and directories

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir search && cd search && mkdir dirA dirA/dirB && touch a_file_with_dir_in_the_name.txt file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

We can search for files and directories using the `find` command:

```sh
find . -name "*.txt"          # From the current directory ("."), search for any anything ending with ".txt"
find . -name "*dir*"          # From the current directory, search for anything with "dir" in the name
find . -type f -name "*dir*"  # Same as above, but only search for files
find . -type d -name "*dir*"  # Same as above, but only search for directories
find $HOME/compphys_examples -type d -name "*dir*"  # Use an absolute path to specify the starting point
```

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r search
```


## Search file content

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir search_file_content && cd search_file_content && wget https://raw.githubusercontent.com/anderkve/FYS3150/master/book/using_the_terminal/extra_material/output.txt && wget https://github.com/anderkve/FYS3150/raw/master/book/using_the_terminal/extra_material/cpp_project.tar && tar -xf cpp_project.tar && echo "" && echo "current directory: $(pwd)" && echo ""
```

The standard tool for searching trough text content is the `grep` command. Using `grep` to search is sometimes referred to simply as "grepping". 
The preparation command above has downloaded [this](https://raw.githubusercontent.com/anderkve/FYS3150/master/book/using_the_terminal/extra_material/output.txt) program output from [this](https://github.com/anderkve/FYS3150/blob/master/book/using_the_terminal/extra_material/random_program.py) to a file `output.txt`. Let's use `grep` to search through it:

```sh
grep "Iteration" output.txt      # Search for and print all lines containing the word "Iteration"
grep -i "error" output.txt       # Use "-i" to ignore differences between upper/lower case letters
grep -n -i "error" output.txt    # Same as above, but include the line number
grep "e+00" output.txt           # Find all lines with numbers of power 10^0
grep -c "e+00" output.txt        # Same as above, but just count the number of lines
grep -v "Error" output.txt       # Matches all lines that *don't* contain the word "Error"
grep -c -v "Error" output.txt    # Count the number of such lines
```

Some symbols have special meanings, e.g. a dot can be used as wildcard to match *any* single character. If we want to actually search for such a special symbol, we have to "escape it" with a backslash first:

```sh
grep "1." output.txt      # This will give a lot of matches...
grep "1\." output.txt     # This will match all numbers containing "1."
```

The search strings for `grep` are so-called **regular expressions**, a technical topic that you can read more about [here](https://en.wikipedia.org/wiki/Regular_expression). 

One of the most common use-cases for `grep` is to search through all files in a project to figure out where some variable or function is being used. Using the `-r` (recursive) option together with `-n` will quickly point you to the relevant file(s) and line numbers:

```sh
grep -r -n "energy" cpp_project/*     # Search for "energy" in all files in the "cpp_project" directory
grep -r -n "init" cpp_project/*       # Search for "init" in all files in the "cpp_project" directory
grep -r -n -C 1 "init" cpp_project/*  # Same as above, but also show one line of context ("-C 1") above/below the search matches.

```

This can be a useful technique when debugging your code, or when you need to find your way through code written by others.

Grepping is often combined with **piping**, which is the next topic below.

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r search_file_content
```
(sec:piping)=
## Piping

**Preparation command:**
```sh
cd $HOME/compphys_examples && mkdir piping && cd piping && mkdir dirA && touch file1.txt file2.txt file3.txt file11.txt file12.txt file13.txt bare.skrot tull.ball && wget https://raw.githubusercontent.com/anderkve/FYS3150/master/book/using_the_terminal/extra_material/output.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

**Piping** means taking the output of one command and passing it directly as input to a second command. This is done using the pipe operator `|`. Here are some examples:

```sh
# Count the number of .txt files in the directory:
# First list all .txt files one by one (ls -l *.txt) 
# and then count the number of lines in the list (wc -l)
ls -l *.txt | wc -l

# List everything in the directory *except* .txt files:
# First list everything in the current directory (ls -l)
# and then remove all lines with ".txt" (grep -v "\.txt")
ls -l | grep -v "\.txt"

# In our previous dummy program output (output.txt), 
# look for errors between iteration 10 and 19:
grep "Iteration 1.:" output.txt | grep "Error" 

# We can also string together multiple pipes. 
# This example will count how many times our dummy 
# program returned a negative number of power 10^1:
grep "e+01" output.txt | grep "-" | wc -l 
```

**Remove example files:**
```sh
cd $HOME/compphys_examples && rm -r piping
```

## Command history

The `history` command displays all commands you've executed recently. Combining it with `grep` and piping can be useful to look for an old command:

```sh
history                    # Display the command history
history | grep "grep"      # List previous grep commands
```

The [keyboard shortcuts](sec:keyboard_shortcuts) page shows other useful ways to search through previous commands.


## Multiple commands in sequence

You can run multiple commands in one go by using a semicolon (`;`) to separate the commands. Let's demonstrate this with the `echo` command, which simply prints a string to screen:

```sh
echo "command one" ; echo "command two" ; echo "command three"
```

If you only want to run the next command *if* the previous command completed successfully, you can use `&&` as separator. So in this next example the third command will *not* be executed, because the second command fails:

```sh
echo "command one" && I-made-a-typo-here && echo "command three"
```

All the single-line preparation commands we've used throughout this page are based on using `;` and `&&` to pack multiple commands into one line.

----

*Congratulations!* If you have worked your way through the above commands you are well on your way to become a true terminal ninja.


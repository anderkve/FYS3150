# Basics 
*or: How I Learned to Stop Worrying and Love the Terminal*


On this page you'll learn the basics of working from the **terminal** (a.k.a. the **shell**, a.k.a. the **command line**). Typing commands instead of the usual point-and-click may feel a bit clumsy and old-fashioned at first. But if you stick with it, you'll soon realize why the terminal is a standard tool for code developers, computational scientists and anyone else doing fancy stuff with computers.

For the examples below we will often need some dummy directories and files. To prepare these files and directories we'll provide one-line *preparation commands* that you can simply copy and paste into the terminal. To paste in the terminal, right-click or press **ctrl-shift-v** (Linux) or **cmd-c** (MacOS)). To execute a command, simply hit 'enter'. 

Don't worry if you don't yet understand everything going on in these preparation commands --- you'll learn all of it soon. Similarly, after each example we provide a single-line command that deletes the dummy files we've just created.

We'll start by creating a directory `compphys_examples/terminal_examples` in our home directory and move into it. This directory will be the starting point for all the examples below.

```sh
mkdir $HOME/compphys_examples && mkdir $HOME/compphys_examples/terminal_examples && cd $HOME/compphys_examples/terminal_examples && echo "" && echo "current directory: $(pwd)" && echo ""
```

```{note}
Don't miss the [keyboard shortcuts](sec:keyboard_shortcuts) listed at the bottom of this page --- they will make your life in the terminal much easier.
```


## Navigation 

**Preparation command:**
```sh
cd $HOME/compphys_examples/terminal_examples && mkdir navigate && cd navigate && mkdir emptydir dirA dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
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
cd /home/yourusername/compphys_examples/terminal_examples  # Move to a directory using its full ('absolute') path
```
**Remove example files:**
```sh
cd $HOME/compphys_examples/terminal_examples && rm -r navigate
```


## Copying, moving and renaming files and directories

**Preparation command:**
```sh
cd $HOME/compphys_examples/terminal_examples && mkdir copy_move_rename && cd copy_move_rename && mkdir emptydir dirA dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
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
cd $HOME/compphys_examples/terminal_examples && rm -r copy_move_rename
```


## Deleting files and directories

**Preparation command:**
```sh
cd $HOME/compphys_examples/terminal_examples && mkdir delete && cd delete && mkdir emptydir dirA dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt && echo "" && echo "current directory: $(pwd)" && echo ""
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
cd $HOME/compphys_examples/terminal_examples && rm -r delete
```

```{note}
*With great power comes great responsibility!* If you delete or overwrite a file/directory by mistake, it is basically gone. (Unless it's a file that is tracked by `git` --- then it's very easy to restore it. You'll learn about that in the git section.) So it can be wise to take a second look before executing a `rm` or `mv` command. For instance, you *never ever* want to do the mistake of accidentally running the command `rm -r /`, which would delete *everything* your user has access to. Another dangerous example is `rm -r *`, which would delete everything in the current directory and all subdirectories --- so you want to make very sure you're in the correct directory... (See below for an explanation of the wildcard `*`.) 
```


## Using wildcards

**Preparation command:**
```sh
cd $HOME/compphys_examples/terminal_examples && mkdir wildcards && cd wildcards && mkdir dirA && touch file1.txt file2.txt file3.txt file11.txt file12.txt file13.txt dirA/file.txt dirA/bare.skrot dirA/tull.ball && echo "" && echo "current directory: $(pwd)" && echo ""
```

The wildcards `*`, `?` and `[]` allow you to perform commands on groups of files/directories. Wildcards can be used with all terminal commands. Here are some examples using the `ls`, `rm` and `mv` commands:

```sh
ls file*             # List files with names beginning with "file"
ls *.txt             # List files with names ending with ".txt"
ls f*.txt            # List files with names beginning with "f" and ending with ".txt"
ls file?.txt         # List files that match "file?.txt" where "?" can be any single character
ls file[123].txt     # List files named "file1.txt", "file2.txt" or "file3.txt"

rm dirA/*.txt        # Delete files in directory dirA with names ending with "_copy.txt"
rm dirA/*            # Delete all files in dirA

mv *.txt dirA/       # Move files ending with ".txt" into the dirA directory
```

**Remove example files:**
```sh
cd $HOME/compphys_examples/terminal_examples && rm -r wildcards
```


## Viewing files

**Preparation command:**
```sh
cd $HOME/compphys_examples/terminal_examples && mkdir view_files && cd view_files && echo "Line number 1" > file1.txt && echo "Line number 2" >> file1.txt && echo "Line number 3" >> file1.txt && echo "Line number 4" >> file1.txt && echo "Line number 5" >> file1.txt && echo "" && echo "current directory: $(pwd)" && echo ""
```

There are several commands for inspecting the content of files directly from the terminal. Below we demonstrate the commands `cat`, `head`, `tail` and `less`. (For a more in-depth explanation, see [here](https://i.redd.it/jlaxkglh1iw41.png).)

```sh
cat file1.txt        # Print the full content of file1.txt to the terminal screen
head -3 file1.txt    # Print the first 3 lines of file1.txt
tail -2 file1.txt    # Print the last 2 lines of file1.txt
less file1.txt       # View file1.txt interactively. Press 'q' to return to the terminal
```

**Remove example files:**
```sh
cd $HOME/compphys_examples/terminal_examples && rm -r view_files
```

```{note}
Viewing files like this only works for text-based (i.e. human readable) files. For files in some binary format, e.g. a compiled C++ program, you won't get sensible output from commands like `cat` and `less`. (Try it and see.)
```


## Download files

**Preparation command:**
```sh
cd $HOME/compphys_examples/terminal_examples && mkdir download_files && cd download_files && echo "" && echo "current directory: $(pwd)" && echo ""
```

If you have the URL you can download a file directly from the terminal with the `wget` command. Let's demonstrate it by downloading the markdown (`.md`) file that this page is built from:

```sh
wget https://raw.githubusercontent.com/anderkve/FYS3150/master/book/using_the_terminal/basics.md

less basics.md   # Take a look at the downloaded file
```

**Remove example files:**
```sh
cd $HOME/compphys_examples/terminal_examples && rm -r download_files
```


<!-- Here! --> 




(sec:keyboard_shortcuts)=
## Keyboard shortcuts

Here are some useful keyboard shortcuts for working in the terminal:

- **Abort a running command:** 
  - *Linux and MacOS:* Use **ctrl-c** to abort a command. You can test this by running the silly command `sleep 10` (does nothing for ten seconds) and abort it with **ctrl-c** before it finishes.

- **Repeat previous commands:** 
  - *Linux and MacOS:* Use **up** and **down** to cycle through previous commands.

- **Auto-complete file/directory names:** 
  - *Linux and MacOS:* Use **tab** to auto-complete long file/directory names. If there are multiple possible matches, press **tab** twice to see the alternatives.

- **Move cursor word by word:** 
  - *Linux:* Use **ctrl-right** and **ctrl-left**
  - *MacOS:* Use **alt-right** and **alt-left**

- **Jump to the beginning/end of the line:**
  - *Linux and MacOS:* Use **ctrl-a** and **ctrl-e**

- **Delete everything after the cursor:**
  - *Linux and MacOS:* Use **ctrl-k**. Thus, a quick way to clear the command line is to press **ctrl-a** and then **ctrl-k**. (Or you can press **ctrl-c**.)

- **Copy/paste:**
  - *Linux:* Use **ctrl-shift-c** and **ctrl-shift-v**
  - *MacOS:* Use **cmd-c** and **cmd-v**

- **Search previous commands:** 
  - *Linux and MacOS:* Press **ctrl-r** and start typing a command. You can press **ctrl-r** again to cycle through alternative matches. Once you found it, press **ctrl-j** or an arrow key to start editing the command.

- **Clear the terminal screen:**
  - *Linux and MacOS:* Press **ctrl-l**. You can also do this by running the command `clear`.

<!--

- [DONE] pwd
- [DONE] cd
- [DONE] ls
- [DONE] mv
- [DONE] rm
- [DONE] rmdir
- [DONE] cat
- [DONE] less
- [DONE] head
- [DONE] tail
- [DONE] wget

- running a script or program

- [DONE] echo "tull"

- pass output to file ">"

- append to file ">>"

- find

- grep

- chmod

- man


- history

- tar and zip

- history


-->
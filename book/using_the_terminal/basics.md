# Basics 
*or: How I Learned to Stop Worrying and Love the Terminal*

<!--

- shift-ctrl-c, shift-ctrl-v (or right click)
- wildcards
- tab completion
- press up/down to run through commands

-->


On this page you'll learn the basics of working from the **terminal** (a.k.a. the **shell**, a.k.a. the **command line**). Working by typing commands instead of the usual point-and-click may feel a bit clumsy and old-fashioned at first. But if you stick with it, you'll soon realize why the terminal is a standard tool for code developers, computational scientists and anyone else doing fancy stuff with computers.

**Preparation**: For the examples below it will be useful to have a test directory `example_basic` that contains some dummy files and subdirectories. To create this, start by opening your terminal application, copy-paste the following command into the terminal (use **ctrl-shift-v** or right-click in the terminal window to paste) and hit 'enter'. 
```sh
mkdir example_basic && cd example_basic && mkdir dirA && mkdir dirA/dirB && touch file1.txt dirA/file2.txt dirA/dirB/file3.txt
```
When you've worked through the examples below you'll understand what this long command actually did.


## Navigation 

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
cd ~                    # (Same as above)
cd /home/yourusername/example_basic/  # Move to a directory using its full ('absolute') path

```


## Copying, moving and renaming files and directories

The basic command for copying is `cp`, and the command for moving and renaming is `mv`. 

```sh
# NOTES: 
#
# - Make sure you start from the 'example_basic' directory.
#
# - If you get confused, use the 'pwd' and 'ls' commands to
#   see where you are and what files/directories are present.

# Copy files
cp file1.txt file1_copy.txt          # Make a copy of file1.txt in the current directory
cp file1.txt dirA/file1_copy.txt     # Make a second copy and place it in dirA

# Copy directories
cp -r dirA dirA_copy                 # Note the -r ('recursive') option for copying directories

# Move files
mv file1.txt dirA/                   # Move file1.txt into the directory dirA

# Rename files and directories
mv file1_copy.txt file1_renamed.txt  # Rename file1_copy.txt to file1_renamed.txt
mv dirA_copy dirA_renamed            # Rename the directory dirA_copy to dirA_renamed
```


## Keyboard shortcuts

There are a bunch of useful keyboard shortcuts you can use when typing commands

- Press **up** and **down** to cycle through the previous commands you've run

- When typing some long file/directory name, press **tab** to auto-complete it. If there are multiple possible matches, press **tab** twice to see the alternatives

- When editing some long command, use **ctrl-right** and **ctrl-left** to move the cursor word by word

- Use **ctrl-shift-c** and **ctrl-shift-v** to copy/paste text

- To search for a command you've run before, press **ctrl-r** and start typing the command. You can press **ctrl-r** again to cycle through alternatives

<!--

## Creating and manipulating files and directories

First of all, we'll create a temporary directory *tmp* that we'll work in (just to avoid an accident).

Once you've opened the terminal, we'll make sure we're in the home directory of our user by running.

```sh
cd
```

Now, to make sure this is the case, we can check our current directory by

```sh
pwd
```

which should output

```sh
home/your_username
```
Now we'll make a directory using *mkdir*

```sh
mkdir tmp
```
We can check that our directory was indeed created by running the *ls* command which lists all files and directories in your current directory:

```sh
ls
```





## Basic commands

- Check your current directory using *pwd*:

  ```sh
  pwd
  ```

  which should simply output the current directory you're in.

- To list all files in a directory, type

  ```sh
  ls
  ```

- Create a file called *filename* using the *touch* command

  ```sh
  touch filename
  ```

- Create a directory using the *mkdir* command

  ```sh
  mkdir directory_name
  ```

- Move a file called *filename* into a subdirectory called *subdir* using the *mv* command

  ```sh
  mv filename subdir
  ```

- Delete a file called *filename* using the *rm* command

  ```sh
  rm filename
  ```
- Copy a file called *filename* into a file *filename_copy* using the *cp* command

  ```sh
  cp filename filename_copy
  ```

- Delete a directory called *dir* and its content using *rm* and the recursive flag *-r*

  ```sh
  rm -r dir
  ```

-->

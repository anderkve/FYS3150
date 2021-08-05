# Basics

Here we'll add a basic introduction to working in the sh.

The *terminal* (or *shell* or *command line*) provides a powerful tool for manipulating files and directories. It's an asset that any developer should know how to utilize.

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

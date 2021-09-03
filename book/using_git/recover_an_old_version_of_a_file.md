(sec:recover_file)=
# Recover an old version of a file

Git tracks the content of your files and keeps their history.
Accidents happen when developing code, and sometimes you break it. In such cases it's convenient to know how to recover an old version of your file. We'll show you how through a hands-on example.

## Hands-on example

First, let's create a file with some text. Run

```sh
echo "The original file. " > my_file.txt
```

Now we'll add, commit and push it to the remote:

```sh
git add my_file.txt && git commit -m "added my_file.txt to learn about recovery of files" && git push
```

Now, we'll modify the file, commit the changes and push it to the remote. Run

```sh
echo "Modified the file. " > my_file.txt
```

and

```sh
git commit -am "modified the file" && git push
```

Feel free to check that the content of the file actually changed.

Now we want to recover the old version of the file. We need to look up the **commit hash** of the previous version to recover it. This is easy -- just run

```sh
git log
```

and look for the commit with the correct commit message. Copy the commit hash (the string of numbers and letters) of this commit. 
Now we can recover the file by

```sh
git checkout COMMIT_HASH_YOU_COPIED my_file.txt
```

This will revert the content of the file back to what it was before you modified it. You can check this by running

```sh
cat my_file.txt
```

Git automatically adds the changes, so you can simply go ahead and commit and push it to the remote:

```sh
git commit -m "recovered the old version of my_file.txt" && git push
```


```{note}
If you want to keep the file you currently have as well, you need to change its name. Otherwise you'll overwrite it in the recovery process.
```

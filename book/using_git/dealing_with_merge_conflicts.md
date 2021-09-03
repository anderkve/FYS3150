# Dealing With Merge Conflicts

In most cases, git **auto-merges** when local branches are merged with `git merge`.
The same applies when you pull from the `remote` to your local branch.


A problem occurs when two people work in the same file and make a commit.
For instance, say you and your partner work in the `main` branch on the same file
and commit your changes separately. Git simply doesn't know how to deal with this
automatically and will throw an error. This error is a **merge conflict**.
This is the intended behaviour of git. In these cases, we will need to resolve
the merging process manually, which we'll look at below through a hands-on example.

## Hands-on example

We'll edit the exact same file from the `main` branch, commit and push it to the remote.
We'll do this from two distinct locations. The result is that only one of the commits will
be accepted, while the other will result in a merge conflict.


First, run the following command in your shell

```sh
echo "This is a line. \nThe original version" > tmp.txt
```

Then add, commit and push it to the remote:

```sh
git add tmp.txt && git commit -m "created tmp.txt to learn about merge conflicts" && git push
```

Next up, run

```sh
cp -r . $(pwd)_copy
```

this will copy all the files in your directory and create a new directory named "repo_name_copy". The directory will be located in the same directory as your original repo directory.

Okay. Now in the original directory of your repo, run

```sh
echo "This is a line. \nThis is version A" > tmp.txt
```

which will overwrite `tmp.txt` with the new message. Then commit, add and push it to the remote, i.e

```sh
git commit -am "created version A of the file" && git push
```

Now enter the copied version of the directory. Run


```sh
echo "This is a line. \nThis is version B" > tmp.txt
```
and

```sh
git commit -am "created version B of the file" && git push
```

Your push will be rejected because your local commit history isn't up-to-date with the remote's. Therefore you will need to pull. Thus run

```sh
git pull
```

This will results in a failure of auto-merging! The last few lines of the output should look something like this:

```sh
Auto-merging tmp.txt
CONFLICT (content): Merge conflict in tmp.txt
Automatic merge failed; fix conflicts and then commit the result.
```

So the punch-line is this: we have to edit the file manually, add and commit it. If you open the file, it will look roughly like this:

```
This is a line.
<<<<<<< HEAD
This is version B
=======
This is version A
>>>>>>> 89c96948fb637b83c1165743fd4e28b87f99e754
```
Couple notes on the output:
- Git has marked the part of the file where the two commits have different content. We are asked to choose between one of them, or create something entirely new there altogether.
- The part between `<<<<<<< HEAD` and `=======` is from your local commit that was rejected when you tried to push.
- The part between `=======` and `>>>>>>> 89c96948fb637b83c1165743fd4e28b87f99e754` is from the commit you made earlier which is now in the remote repo.
- The long string of numbers and letters is called the **commit hash** and is simply a unique string that identifies the commit.


The solution here is simple. Us, the user, must choose version A or version B manually. This means we just delete the content we don't want, add and commit it the final version and push it. We'll just choose the following content here:

```
This is a line.
This is version B
```

Now just run

```sh
git commit -am "Resolved the conflict, chose version B" && git push
```

And that's sums up the process of resolving merge conflicts.

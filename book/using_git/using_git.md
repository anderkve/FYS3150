# Using Git


## Synopsis

This tutorial explains how to import a new project into Git, make changes to it, and share changes with other developers. It's a slightly modified and extended version of the manual entry called *gittutorial*, which you can look up in your terminal by running

```sh
man gittutorial
```


```{note}
As explained below, a Git repository is organised into *branches*. For repositories created before October 1, 2020, the main branch was by default called `master`. Therefore, if you work on older projects, you might see the main branch called `master` instead of `main`.
```


## Cloning a new project

We recommend you create a repository online on [GitHub](https://github.com/) and clone the repository on your computer using the HTTPS link. It's simply done by running

```sh
git clone https_link
```

where `https_link` is the URL for your repo on GitHub.


## Making changes

Modify some files, then add their updated contents to the index:

```sh
git add file1 file2 file3
```

You are now ready to commit. You can see what is about to be committed
using `git diff` with the --cached option:

```sh
git diff --cached
```


(Without --cached, `git diff` will show you any changes that you've made
but not yet added to the index.) You can also get a brief summary of
the situation with `git status`:

```sh
git status
On branch main
Changes to be committed:
Your branch is up to date with 'origin/main'.
  (use "git restore --staged <file>..." to unstage)

        modified:   file1
        modified:   file2
        modified:   file3
```

```{note}
We recommend making it a habbit to run `git status` whenever you are unsure about the current status of your repository, and as a first step whenever you encounter a problem. The output of `git status` will often tell you exactly what you need to do.
```


If you need to make any further adjustments, do so now, and then add
any newly modified content to the index. Finally, commit your changes
with:

```sh
git commit
```


This will again prompt you for a message describing the change, and
then record a new version of the project.

Alternatively, instead of running `git add` beforehand, you can use

```sh
git commit -a
```

which will automatically notice any modified (but not new) files, add
them to the index, and commit, all in one step.

A note on commit messages: Though not required, it's a good idea to
begin the commit message with a single short (less than 50 character)
line summarizing the change, followed by a blank line and then a more
thorough description. The text up to the first blank line in a commit
message is treated as the commit title, and that title is used
throughout Git.


## Git tracks content, not files

Many revision control systems provide an **add** command that tells the
system to start tracking changes to a new file. Git's **add** command does
something simpler and more powerful: `git add` is used both for new and
newly modified files, and in both cases it takes a snapshot of the
given files and stages that content in the index, ready for inclusion
in the next commit.


## Viewing project history

At any point you can view the history of your changes using

```sh
git log
```

If you also want to see complete diffs at each step, use

```sh
git log -p
```

Often the overview of the change is useful to get a feel of each step

```sh
git log --stat --summary
```

## Managing branches


A single Git repository can maintain multiple branches of development.
To create a new branch named `experimental`, use

```sh
git branch experimental
```

If you now run

```sh
git branch
```

you'll get a list of all existing branches:

```sh
  experimental
* main
```


The `experimental` branch is the one you just created, and the `main`
branch is a default branch that was created for you automatically. The
asterisk marks the branch you are currently on; type

```sh
git switch experimental
```


to switch to the experimental branch.

```{note}
`git switch` requires Git version 2.23 or later. You can use `git checkout` as a replacement if you use an older version of Git.  
```

Now edit a file, commit the
change, and switch back to the `main` branch:

```sh
(edit file)
git commit -a
git switch main
```

Check that the change you made is no longer visible, since it was made
on the experimental branch and you're back on the `main` branch.

You can make a different change on the `main` branch:

```sh
(edit file)
git commit -a
```

at this point the two branches have diverged, with different changes
made in each. To merge the changes made in experimental into `main`,
run

```sh
git merge experimental
```

```{note}
Keep in mind that `git merge some_branch_name` merges changes *from* `some_branch_name` *into* the branch you are currently in. So if you are unsure, run `git branch` first to check that you are in the correct branch. Also it is recommended to not have any uncommited changes in the current branch when you do the merge.
```

If the changes don't conflict, you're done. If there are conflicts,
markers will be left in the problematic files showing the conflict;

```sh
git diff
```

will show this. (Also, running `git status` at this point will give you a summary of which files have conflicts and what you need to do.) Once you've edited the files to resolve the conflicts,

```sh
git commit -a
```

will commit the result of the merge. Finally,

```sh
gitk
```


will show a nice graphical representation of the resulting history.

At this point you could delete the experimental branch with

```sh
git branch -d experimental
```


This command ensures that the changes in the experimental branch are
already in the current branch.

If you develop on a branch `crazy-idea`, then regret it, you can always
delete the branch with

```sh
git branch -D crazy-idea
```

Branches are cheap and easy, so this is a good way to try something out.


## Collaborating using GitHub

So far we've only discussed Git locally on your computer, but not how we collaborate with other developers. This is where GitHub comes into the picture.

It's customary to work on different branches to protect the content of the `main` branch. Just like in the example above where we worked on a branch called `experimental`, you can create your own branch when you work on a project with other people.


### Pull any changes from the remote

The **remote** repo is the term used for the cloud-based (GitHub) version of your local Git repo. To **pull** down any changes done by the other developers on a branch, run

```sh
git pull origin branchname
```
In particular, to pull from the `main` branch, run

```sh
git pull origin main
```

The name `origin` is just the standard name assigned to the remote repo, i.e. the repo living on GitHub. So this command is effectively saying *pull down any changes from the `main` branch on the GitHub repo, and merge these into the current branch of my local repo.*


### Push your changes to the remote

When you've performed local changes to a branch, you can push them to the remote using

```sh
git push origin branchname
```

again, for the main branch, this is done by

```sh
git push origin main
```


```{note}
It's a good idea to always pull from `origin` before you try to merge branches locally, commit or push to `origin`. Always sync up with the remote version of the repo first!
```

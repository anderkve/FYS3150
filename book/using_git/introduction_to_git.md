# Introduction to git

## What is git?

*git* is a version control software, or as the developers themselves call it, a *stupid content tracker*. What it *does* is track changes in a system of files to make collaboration among developers on a code project easy. It provides a rich set of tools to ensure that several programmers can work on the same project in a non-linear way. Several programmers can even work on the exact same file.

## What is GitHub?

GitHub is a service that provides hosting and storage for software development and version control using git as its underlying version control software. It also offers services that goes beyond the functionality of git.

For our purposes, they host *repositories*, or *repos* for short, that essentially are copies of specific local computer directories at certain timestamps. We use git to manage these and store copies on a server hosted by GitHub.


## Synopsis

This tutorial explains how to import a new project into Git, make
changes to it, and share changes with other developers. It's a slightly modified and extended version of the manual entry of *gittutorial*. At any point, you can look this up in your terminal should you forget it by running

```sh
man gittutorial
```


## Importing a new project

Assume you have a tarball project.tar.gz with your initial work. You
can place it under Git revision control as follows.

```sh
tar xzf project.tar.gz
cd project
git init
```

Git will reply

```sh
Initialized empty Git repository in .git/
```


You've now initialized the working directory--you may notice a new
directory created, named ".git".

Next, tell Git to take a snapshot of the contents of all files under
the current directory (note the `.`, it means "the current directory"), with `git add`:

```sh
git add .
```


This snapshot is now stored in a temporary staging area which Git calls
the "index". You can permanently store the contents of the index in the
repository with `git commit`:

```sh
git commit
```

This will prompt you for a commit message. You've now stored the first
version of your project in Git.

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
On branch master
Changes to be committed:
Your branch is up to date with 'origin/master'.
  (use "git restore --staged <file>..." to unstage)

        modified:   file1
        modified:   file2
        modified:   file3
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


Many revision control systems provide an aadddd command that tells the
system to start tracking changes to a new file. Git's aadddd command does
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
To create a new branch named "experimental", use

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
* master
```


The "experimental" branch is the one you just created, and the "master"
branch is a default branch that was created for you automatically. The
asterisk marks the branch you are currently on; type

```sh
git switch experimental
```


to switch to the experimental branch. Now edit a file, commit the
change, and switch back to the master branch:

```sh
(edit file)
git commit -a
git switch master
```

Check that the change you made is no longer visible, since it was made
on the experimental branch and you're back on the master branch.

You can make a different change on the master branch:

```sh
(edit file)
git commit -a
```

at this point the two branches have diverged, with different changes
made in each. To merge the changes made in experimental into master,
run

```sh
git merge experimental
```

If the changes don't conflict, you're done. If there are conflicts,
markers will be left in the problematic files showing the conflict;

```sh
git diff
```

will show this. Once you've edited the files to resolve the conflicts,

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

If you develop on a branch crazy-idea, then regret it, you can always
delete the branch with

```sh
git branch -D crazy-idea
```

Branches are cheap and easy, so this is a good way to try something
out.


## Using git for collaboration; Using GitHub

So far we've only discussed git locally on your computer, but not how we collaborate with other developers. This is where GitHub comes into the picture.

It's customary to work on different branches to protect the content of the main branch. Just like in the example above where we worked on a branch called "experimental", you can create your own branch when you work on a project with other people.


### Pull any changes from the remote

The **remote** repo is the term used for the cloud based copy of your local git repo. To **pull** down any changes done by the other developers on a branch, run

```sh
git pull origin branchname
```

in particular, to pull from the `main` branch, run

```sh
git pull origin main
```

```{note}
For old repositories created before October 1, 2020, the main branch was called master. Therefore, if you work on projects created before this, you might see the main branch called "master" instead.
```

### Push your changes to the remote

When you've performed local changes to a branch, you can push it to the remote using

```sh
git push origin branchname
```

again, for the main branch, this is done by

```sh
git push origin main
```


```{note}
It's a good idea to always pull from the origin before you try to merge branches locally, commit or push to the origin. Always sync up with the remote version of the repo first!
```

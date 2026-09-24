# Dealing with merge conflicts

When you merge one branch into another, Git combines the changes from both branches automatically. The same happens when you run `git pull`, which merges the remote branch into your local one. But if the two branches have changed the *same lines* of the same file, Git cannot know which version you want. It stops and reports a **merge conflict**, and you have to finish the merge by hand. This is normal, and the fix is simple: edit the file, then `git add` and `git commit`.

If you follow the [workflow for collaborating](sec:git_collab_workflow) on the previous page, conflicts show up in step 3, when you merge `main` into your own branch. Below we recreate that situation with a small example.


## Hands-on example

Start on `main` and create a file with two lines:

```sh
git switch main
printf "This is a line.\nThe original version\n" > tmp.txt
git add tmp.txt
git commit -m "Add tmp.txt to learn about merge conflicts"
```

Create a new branch and change the second line there:

```sh
git branch conflict-demo
git switch conflict-demo
printf "This is a line.\nThis is version A\n" > tmp.txt
git add tmp.txt
git commit -m "Create version A"
```

Now play the role of your partner: switch back to `main` and change the same line differently:

```sh
git switch main
printf "This is a line.\nThis is version B\n" > tmp.txt
git add tmp.txt
git commit -m "Create version B"
```

Finally, go back to your branch and merge `main` into it, as in step 3 of the workflow:

```sh
git switch conflict-demo
git merge main
```

Git fails to merge automatically:

```
Auto-merging tmp.txt
CONFLICT (content): Merge conflict in tmp.txt
Automatic merge failed; fix conflicts and then commit the result.
```


## Resolving the conflict

Open `tmp.txt` in an editor. It now looks like this:

```
This is a line.
<<<<<<< HEAD
This is version A
=======
This is version B
>>>>>>> main
```

Git has marked the region where the two branches disagree. The part between `<<<<<<< HEAD` and `=======` is the version on your current branch. The part between `=======` and `>>>>>>> main` is the version on the branch you are merging in. (After a `git pull`, the last marker shows a commit hash instead of a branch name.)

To resolve the conflict, edit the file so that it contains what you want: version A, version B, or a combination of the two. Remove the marker lines. For instance:

```
This is a line.
This is version B
```

Then stage the file and commit to complete the merge:

```sh
git add tmp.txt
git commit -m "Merge main into conflict-demo, keep version B"
```

That is all. Your branch now contains the changes from both branches, and you can carry on with step 4 of the workflow. If several files have conflicts, repeat the edit and `git add` for each of them before you commit.

```{note}
During a conflict, `git status` lists the files that still need attention. If you want to give up on the merge and return to the state before you ran `git merge`, run `git merge --abort`.
```

To clean up after the example, switch to `main`, delete the branch with `git branch -D conflict-demo`, and remove the file with `git rm tmp.txt` followed by a commit.

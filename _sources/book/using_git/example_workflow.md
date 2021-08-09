# Example workflow

Here we'll add info on an example workflow for git


## Tracking new files

Once a new file is created/added, git needs to track it (or rather its content  ). In the example below, we've created a file *test.py*.

- First we check the *status* by running

  ```sh
  git status
  ```
  ![untracked_file](./imgs/untracked_file.png)

- git outputs that the file is untracked. We *add* the file so git can track it by

  ![tracked_file](./imgs/add_file.png)

Now, any git will record any changes we make in the file.

- More generally, we can add multiple files by

```sh
git add filename_1 filename_2 ... filename_N
```

- Or the lazier approach if you just want to add everything

```sh
git add --all
```

## Commit and push changes to the cloud

Once you've added your changes, you should *commit* these and *push* them to your branch.

- The general command for commits is

  ```sh
  git commit -m "short informative message about the changes you commit"
  ```

- In the case of our example, this looks like

  ![commit](./imgs/commit_file.png)

- The next step is to *push* the changes up to the cloud storage of your repository. Generically, do this by

  ```sh
  git push origin branch_name
  ```

- In our toy example, we're on the branch called *main*. Thus

  ![push](./imgs/push.png)


## Creating branches

It's usually wise to work on a different branch than the main branch when developing new code. This is to protect the work that you've already developed.

To create a new branch, let's call it *experimental*, simply run

```sh
git branch experimental
```

To check the available branches, run

```sh
git branch
```

which should output

```sh
*main
experimental
```

The star indicates the branch you're currently working in. To switch branch to experimental, run

```sh
git switch experimental
```

## Merging branches

Once you've developed some new code that works, it's time to bring it into the main branch to become part of the main project. This happens in three steps:

1. Add and commit the changes.
2. Change to the main branch
3. Merge the branches

Once the process is completed, the content of the branches will be identical.

If you've created any new files, we must add them for git to track their content:

```sh
git add --all
```

Otherwise, we can simply run

```sh
git commit -a -m "commit message"
```

the *-a* flag adds any content changes to files that already existed. (So it does not work for new files that isn't tracked yet).

Now, we switch to the main branch

```sh
git switch main
```

Finally, we can merge with the experimental branch with the following

```sh
git merge experimental
```

If there's no conflicts, then this can simply be commited and pushed to the cloud as usual.

## Dealing with conflicts

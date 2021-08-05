# Example workflow

Here we'll add info on an example workflow for git


## Tracking new files

Once a new file is created/added, git needs to track it. In the example below, we've created a file *test.py*.

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


## Merging branches

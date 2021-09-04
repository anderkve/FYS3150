# Other ways to fix mistakes

In terms of fixing mistakes using git, to [recover the old state of a file](sec:recover_file) is probably the approach we most often need. However, there are plenty of other ways to fix problems. Below we have collected a few git tricks, inspired by the collection in [this](https://www.smashingmagazine.com/2021/05/undoing-mistakes-git-part1/) article by Tobias Günther.


- You can discard all the *uncommitted* changes in a file, i.e. **restore** the file to its *previous committed state*, using `git restore`:
  ```sh
  git restore my_file
  ```

- Do you regret some changes you made and committed a while back, say the changes in commit `7g430yqx`? 
  You can **revert** the changes in a specific commit with the command `git revert`, e.g. 
  ```sh
  git revert 7g430yqx
  ```
  Note that this will *not* go back into the repo history and delete the commit `7g430yqx` -- that could cause trouble. Rather, it will will add a *new* commit that reverts the changes in commit `7g430yqx`.

- Perhaps you've just messed up properly, with silly changes all over the place, and now you just want things to go back to the way they were before?
  (I know, we all feel like this sometimes...) Well, there's a git command for that: `git reset` can **reset** your *entire repo* to a previous commit, e.g.
  ```sh
  git reset --hard 7g430yqx
  ```

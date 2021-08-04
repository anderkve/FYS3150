# Introduction to git

Here we'll add some info on how to get started using git for version control.


## Setting up git on your computer

You need to tell Git which user you are. Write the following commands in your terminal.

```terminal
$ git config --global user.name "Your Name Comes Here"

$ git config --global user.email you@yourdomain.example.com
```

## Create a Github repository for the course

Here's a step-by-step instruction.

- Go to [github.com](Github.com) and log in. The page should look something like this:

![homepage](./imgs/github_homepage.png)

- Click on the green button named *New*. You should be redirected to a page that looks like this:

![create_repo](./imgs/create_repo.png)

- Fill out your desired repository name, for instance *fys3150*
  - Keep the repository *public*.
  - Toggle *add a README file*.
  - Click *create repository*.
  - You'll be automatically redirected to the home page of your repository, see the image below.

![clone_repo](./imgs/clone_repo.png)

- Clone your repository to your computer.  
  - Click on the green button named *code*.
  - Copy the link.
  - Run in your terminal:
    ```terminal
    git clone the_repository_link_you_copied
    ```

Now you've cloned the repository to your computer! This will be a directory you can now find locally on your computer.



## Adding a Github token
*Only for Linux and Windows users. This is done automatically on macOS. In any case, if you're requested to write your password more than once on macOS, follow the steps in this guide.*

A Github token is a replacement of passwords to give you as a user access to perform action on your Github repositories from your computer.

Disclaimer: Note that this is not a secure option, as the token will be saved in clear text. But it's nevertheless the simplest option.


- Go to [github.com](www.github.com). Click on your profile in the upper right corner, then on *settings*.

![go_to_settings](./imgs/go_to_settings.png)

- Click on *developer settings*.

![go_to_developer_settings](./imgs/go_to_developer_settings.png)

- Click on *Personal access tokens* and then click on *Generate new token*.

![generate_new_token](./imgs/generate_new_token.png)

- Your page should look somethings like what follows.
    - Fill out note with a name for the token, for instance *main_token*.
    - Change expiration date to *no expiration* (you can choose a finite expiration if security bothers you. But this is a school project, not a multibillion dollar code project.)
    - Toggle every box under *select scopes*. Most of them are unecessary, but we just want full access.
    - Click *Generate token* at the bottom of the screen.

![token_page](./imgs/token_page.png)

- You'll be redirected to the page with tokens now. *Make sure you copy it!*


- In your Github repository (locally on your computer), run.

  ```terminal
  git config --global credential.helper store
  ```

- Then run

  ```terminal
  git pull
  ```

- Type in your username (you'll be prompted to do so.)

- Paste in the token you copied instead of your password.

And you're done!

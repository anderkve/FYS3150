# Mac users

Here we'll add info to help Mac users get their system set up for this course.

Installation of software for C++ can be a little bit of a hazzle on macOS. This page will walk you through the process, step-by-step.

## Installation of basic software

1. First install *Xcode* from the app store. This contains the basic building blocks we need. It installs *git* and *Make* and a few other command line tools.

2. Now we'll install a *package manager* which we'll use install many other packages. Go to [Homebrew](https://brew.sh) and follow the installation instruction there. It's easy, just copy the link they provide there and run it in your terminal.


3. Now, run the following command in your terminal
    ```sh
    brew install armadillo libomp git-gui
    ```


## Additional useful command line tools

There's a plethora of useful command line tools for macOS that can be useful.

1. *wget* and *curl* are command line tools that allow you to download from the web using the command line.

2. *htop* is a powerful task manager that also displays the work each thread uses graphically in your terminal. This is a useful tool when you're code is parallelized (later in the course) so that you can monitor the work each thread does.

3. *tree* is a convenient tool to display files and directories in the terminal.


To install these, simply run

```sh
brew install wget curl htop tree
```

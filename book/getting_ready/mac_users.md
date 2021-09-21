# Mac users

Here we'll add info to help Mac users get their system set up for this course.

Installation of software for C++ can be a little bit of a hazzle on macOS. This page will walk you through the process, step-by-step.

## Installation of basic software

1. First install *Xcode* from the app store. This contains the basic building blocks we need. It installs *git* and *Make* and a few other command line tools.

2. Now we'll install a *package manager* which we'll use install many other packages. Go to [Homebrew](https://brew.sh) and follow the installation instruction there. It's easy, just copy the command they provide there and run it in your terminal.


3. Now, run the following command in your terminal
    ```sh
    brew install armadillo libomp git-gui
    ```


### M1 Mac users
If you've bought a Mac after November 2020, then you might have a so-called M1 Mac. In that case, Homebrew defaults its installation to a different path than the the Intel based ones do. Therefore, in order for the compiler to find Armadillo, you must copy the installed files to the correct directory. This is easy, simply copy and run the following commands and type in your password if prompted:

```sh
sudo cp -r /opt/homebrew/Cellar/armadillo/10.6.2/lib/* /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib
```

```sh
sudo cp -r /opt/homebrew/Cellar/armadillo/10.6.2/include/armadillo* /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
```

This should do the trick. Please open a Github issue in case it doesn't work for you.

## Additional useful command line tools

There's a plethora of useful command line tools for macOS that can be useful.

1. *wget* and *curl* are command line tools that allow you to download from the web using the command line.

2. *htop* is a powerful task manager that also displays the work each thread uses graphically in your terminal. This is a useful tool when you're code is parallelized (later in the course) so that you can monitor the work each thread does.

3. *tree* is a convenient tool to display files and directories in the terminal.


To install these, simply run

```sh
brew install wget curl htop tree
```

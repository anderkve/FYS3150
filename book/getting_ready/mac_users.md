# Mac users

Installation of software for C++ can be a little bit of a hassle on macOS. This page will walk you through the process, step-by-step.

## Installation of basic software

1. First, install *Xcode* from the app store. This contains the basic building blocks we need. It installs *Git* and *Make*, along with a few other command line tools. (Note that Xcode unfortunately is a very large package -- over 12 GBs, and may even require substantially more available disk space than this for the installation.)

2. Now we'll install a *package manager* which we'll use to install many other packages. Go to [Homebrew](https://brew.sh) and follow the installation instructions there. It's easy, just copy the command they provide there and run it in your terminal.


3. Now, run the following command in your terminal to install some additional C++ libraries we'll use (Armadillo and OpenMP).
    ```sh
    brew install armadillo libomp
    ```


## Additional setup for M1 Mac users
If your Mac is sufficiently new (since late 2020), then you might have a so-called "M1 Mac", that is a Mac based on the Apple M1 processor. (An alternative name for these processors is "Apple silicon".) Older Macs are based on Intel processors. 

To check if you have an M1-based or Intel-based Mac, click the Apple logo in the top-left corner, select "About This Mac", and see what it says under "Chip". (See an example [here](https://support.apple.com/en-us/HT211814).)

Homebrew uses a different default installation directory on M1 Macs compared to on the older Intel-based Macs. So in order for the C++ compiler to find the Armadillo library, you must copy the installed files to the correct directory. This is easy, simply copy and run the following commands and type your password if prompted:

```sh
sudo cp -r /opt/homebrew/Cellar/armadillo/11.2.3_1/lib/* /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib
```

```sh
sudo cp -r /opt/homebrew/Cellar/armadillo/11.2.3_1/include/armadillo* /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
```

This should do the trick. Please open an issue on our GitHub page if this doesn't work for you.


## Install additional command line tools

There's a plethora of command line tools that can be useful. Here are some examples:

1. *wget* and *curl* are command line tools that allow you to download from the web using the command line.

2. *htop* is a powerful task manager that also displays the work each thread uses graphically in your terminal. This is a useful tool when you're code is parallelized (later in the course) so that you can monitor the work each thread does.

3. *tree* is a convenient tool to display files and directories in the terminal.


To install these, simply run

```sh
brew install wget curl htop tree
```

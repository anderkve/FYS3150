# Mac users

(sec:choosing_shell)=
## Choosing a Unix shell

The [Unix shell](https://en.wikipedia.org/wiki/Unix_shell) (Unix command line interface) comes in a few different versions, with `bash` and `zsh` being among the most widely used. Most commands are identical across different shells, but in some cases there are small differences. One [example](https://superuser.com/questions/420525/scp-with-zsh-no-matches-found) is commands that use [wildcards](sec:wildcards) like `*`, where `zsh` might require you to [add quotation marks](https://superuser.com/a/1212433) around the command arguments, or ["escape" the wildcard](https://superuser.com/a/625864) by writing `\*` instead of `*`.

The commands listed on our course pages have generally been tested on `bash`, which is the default shell on Ubuntu Linux. It was also the default on Mac until macOS 10.15 Catalina, when Mac switched to use `zsh` as default.

To see which shell you are currently running, open a terminal and run the command 

```sh
echo $0
```
This will give the path to the shell you are running, which will probably be `/bin/bash` or `/bin/zsh`. 

It's easy to change the default shell -- have a look [here](https://support.apple.com/en-us/HT208050) for point-and-click instructions, or simply run the command 

```sh
chsh -s /bin/bash
```

to set `bash` as default, or run 

```sh
chsh -s /bin/zsh
```

to set `zsh` as default. Note that you probably have to close and restart your terminal for this change to take effect.

If you want to switch shell just for your current terminal session, rather than setting a new default, you can do that simply by running 
```sh
zsh
```
or
```sh
bash
```


(sec:installation_of_basic_software)=
## Installation of basic software

Installation of software for C++ can be a little bit of a hassle on macOS. Here we'll try to walk you through the process, step-by-step.

1. First, install *Xcode* from the app store. This contains the basic building blocks we need. It installs *Git* and *Make*, as well as a few other command line tools. (Note that Xcode unfortunately is a very large package -- over 12 GBs, and may even require substantially more available disk space than this for the installation.)

2. Now we'll install a *package manager* which we'll use to install many other packages. Go to [Homebrew](https://brew.sh) and follow the installation instructions there. It's easy, just copy the command they provide there and run it in your terminal.


3. Now, run the following command in your terminal to install some additional C++ libraries we'll use (Armadillo and OpenMP).
    ```sh
    brew install armadillo libomp
    ```


## Additional setup for M1 Mac users
If your Mac is sufficiently new (since late 2020), then you might have a so-called "M1 Mac", that is a Mac based on the Apple M1 processor. (An alternative name for these processors is "Apple silicon".) Older Macs are based on Intel processors. 

To check if you have an M1-based or Intel-based Mac, click the Apple logo in the top-left corner, select "About This Mac", and see what it says under "Chip". (See an example [here](https://support.apple.com/en-us/HT211814).)

Homebrew uses a different default installation directory on M1 Macs compared to on the older Intel-based Macs. So in order for the C++ compiler to find the Armadillo library, you must copy the installed files to the correct directory. 

First, check which version of Armadillo that Homebrew installed on your system by listing the content of the directory `/opt/homebrew/Cellar/armadillo`:

```sh
ls /opt/homebrew/Cellar/armadillo
```

Here you should see a directory with the version number, e.g. `10.6.2` or `11.2.3_1` or similar. Now run the copy commands below, adjusted to use your Armadillo version number in the paths. For version `11.2.3_1` the commands are:

```sh
sudo cp -r /opt/homebrew/Cellar/armadillo/11.2.3_1/lib/* /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib
```

```sh
sudo cp -r /opt/homebrew/Cellar/armadillo/11.2.3_1/include/armadillo* /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
```

Since we use `sudo` here you will (probably) have to type in your password. 



## Install additional command line tools

There's a plethora of command line tools that can be useful. Here are some examples:

1. *wget* and *curl* are command line tools that allow you to download from the web using the command line.

2. *htop* is a powerful task manager that also displays the work each thread uses graphically in your terminal. This is a useful tool when your code is parallelized (later in the course) so that you can monitor the work each thread does.

3. *tree* is a convenient tool to display files and directories in the terminal.


To install these, simply run

```sh
brew install wget curl htop tree
```

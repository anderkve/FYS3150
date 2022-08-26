# Windows users

## Installing Windows Subsystem for Linux (WSL)

There's an excellent guide on how to install WSL [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10). Follow the **manual installation**.


Once you've completed the installation of WSL and Ubuntu, run the following command in your Linux terminal:

```sh
sudo apt update && sudo apt upgrade
```

You'll get prompted to enter your password. Do so and it'll run for a while. Once finished, follow the guide for [Linux users](linux_users.md) to install the Linux libraries and tools you'll need. (But come back here afterwards and read the rest of this page!)


```{note}

If you have installed WSL/Ubuntu but run into trouble when trying to start the actual Linux terminal (shell), try this:

In your Windows powershell, run the command `wsl --set-default-version 1`

then try to restart the Linux terminal. This has worked for a few students. We'll update this guide if we figure out more about what the underlying issue is.
```


## How to access/edit your Linux files with Windows applications

A nice work setup for many WSL users will be to keep all your project files on the Linux part of the computer, so you can compile, run, perform git commands etc. with your Linux (Ubuntu) terminal, but still use Windows applications to edit the files, e.g. through Visual Studio Code or whatever editor you already use.

On Windows, the Linux (WSL) part of your system will appear as a network drive. To get the full path of your Linux home directory as seen from Windows, start the Linux terminal and then launch the *Windows* file explorer using the command:

```
explorer.exe .
```

(Make sure to include the dot, which tells explorer.exe to open the current directory you are in.)

Now you see your Linux files in the Windows file explorer. It's useful to now create a shortcut for e.g. your user's Linux home folder and put this shortcut in the quick-access bar (the left-hand part) of the Windows file explorer. Then from any Windows application you can easily open/edit/save files in the Linux part of your system. See [here](https://docs.microsoft.com/en-us/windows/wsl/filesystems#view-your-current-directory-in-windows-file-explorer) and [here](https://www.howtogeek.com/426749/how-to-access-your-linux-wsl-files-in-windows-10/) for more details.


## Enable ctrl+shift+c/v for copy/paste in the terminal

On WSL, copy/paste in the Linux terminal using the standard Linux keyboard shortcuts ctrl+shift+c and ctrl+shift+c will not work by default. To enable it 

  - click the small Ubuntu icon in the top-left corner of your terminal
  - choose *Properties*
  - select the *Options* pane
  - tick the box saying "Use Ctrl+Shift+C/V as Copy/Paste"

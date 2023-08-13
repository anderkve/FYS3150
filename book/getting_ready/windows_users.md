# Windows users

## Installing Windows Subsystem for Linux (WSL)

- Install WSL by following the guide(s) [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

- Once you've installed WSL and Ubuntu, run this command in your Linux terminal: 
  ```sh
  sudo apt update && sudo apt upgrade
  ```
  (You will be asked to enter your password when running this command.) 

- Next, follow our guide for [Linux users](linux_users.md) to install the Linux libraries and tools you'll need.


```{note}

If you have installed WSL but run into trouble when trying to start the actual Linux terminal (shell), try this:

In your Windows PowerShell, run the command `wsl --set-default-version 1` and then restart the Linux terminal. This has worked for a few students. We'll update this guide if we figure out more about what the underlying issue is.
```


## How to access your Linux files from Windows applications

A nice setup for many WSL users will be to keep all your project files on the Linux part of the computer, so you can compile, run, perform git commands etc. with your Linux (Ubuntu) terminal, but still use Windows applications to edit the files, e.g. through Visual Studio Code or whatever editor you already use.

On Windows, the Linux (WSL) part of your file system will appear as a network drive. To get the full path of your Linux home directory as seen from Windows, start the Linux terminal and then launch the *Windows file explorer* using the command:

```
explorer.exe .
```

(Make sure to include the dot. It tells `explorer.exe` to open the directory you are currently in.)

Now you see your Linux files in the Windows file explorer. It's useful to now create a shortcut for e.g. your user's Linux home folder and put this shortcut in the quick-access list (the left-hand part) of the Windows file explorer. Then from any Windows application you can easily open/edit/save files in the Linux part of your system. To add a folder to the quick-access list, just right-click it and select *pin to Quick access*. See [here](https://docs.microsoft.com/en-us/windows/wsl/filesystems#view-your-current-directory-in-windows-file-explorer) and [here](https://www.howtogeek.com/426749/how-to-access-your-linux-wsl-files-in-windows-10/) for more details.


## How to access your Windows files from the Linux terminal

From the Linux terminal, a Windows drive like `C:\` will appear as the folder `mnt/c`. So if you need to refer to some Windows folder `C:\your\folder` from a Linux command, you should use the path `mnt/c/your/folder`. See [here](https://askubuntu.com/a/943023) for more details.


## Enable ctrl+shift+c/v for copy/paste in the terminal

On WSL, copy/paste in the Linux terminal using the standard Linux keyboard shortcuts **ctrl+shift+c** and **ctrl+shift+v** may not work by default. To activate these shortcuts, do this:

  - Click the small Ubuntu icon in the top-left corner of your terminal
  - Choose *Properties*
  - Select the *Options* pane
  - Tick the box saying "Use Ctrl+Shift+C/V as Copy/Paste"

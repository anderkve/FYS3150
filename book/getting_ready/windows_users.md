# Windows users

## Installing Windows Subsystem for Linux (WSL)

There's an excellent guide on how to install WSL [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10). Follow the **manual installation**.


Once you've completed the installation of WSL and Ubuntu, run the following command in your Linux terminal:

```sh
sudo apt update && sudo apt upgrade
```

You'll get prompted to enter your password. Do so and it'll run for a while. Once finished, follow the guide for [Linux users](linux_users.md).


## Troubleshooting

If you manage to install WSL/Ubuntu but run into trouble when trying to start the actual terminal (shell), try this:

In your Windows powershell, type

```sh
wsl --set-default-version 1
```

then try to restart the Linux terminal.

```{note}
This has worked for a few students. We'll update this guide if we figure out more about what the underlying issue is.
```

# Windows users

## Setting up Windows Subsystem for Linux (WSL)


There's an excellent guide on how to install WSL [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

Once you've completed the installation of WSL and Ubuntu, follow the guide for [Linux users](linux_users.md).


## Troubleshooting

If you manage to install WSL/Ubuntu but run into trouble when trying to start the actual shell, try this:

In your windows powershell type

```sh
wsl --set-default-version 1
```

then try to restart the linux shell. This has worked for other students, we don't remember the exact error but it had something to do with BIOS or something :-)))))

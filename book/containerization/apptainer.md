# Apptainer

Within the context of this course, there are a number of dependencies required to develop code for the projects (such as `g++` for compilation, `git` for version control, `Armadillo`, `OpenMP`, etc.). The instructors have put together an image (essentially the blueprint for a container) which wraps all of these together, using the application [Apptainer](https://apptainer.org/docs/user/latest/introduction.html).

This guide will help you set up and run this Apptainer image for the course on your machine, whether you're using Linux, Windows, or macOS (Intel or ARM architecture).

## Getting Started

### Step 1: Apptainer Installation

Apptainer is primarily designed to run natively on Linux systems, because it leverages key Linux kernel features such as namespaces and control groups to provide containerization. Therefore, non-Linux systems (i.e. Windows and macOS) require an additional layer to create a virtualized or emulated Linux environment.

#### Installation on Windows

On Windows, the Linux environment is handled by WSL. Therefore, once it is installed (see [Windows users](sec:windows_users)), you can follow the instructions for installation on Linux below.

#### Installation on Mac

On Mac, the recommended path to setting up a Linux environment is through [Lima](https://lima-vm.io/docs/), which is a lightweight virtual machine manager designed to run Linux environments efficiently on macOS.

The first step to working with Lima is to install it with Homebrew (see [installation of basic software](sec:installation_of_basic_software) if you haven't yet installed the Homebrew package manager on your machine):

```bash
brew install lima
```

Next, run the following command to initialize a new Linux VM specifically configured to work with Apptainer:

```bash
limactl start template://apptainer
```

Out-of-the-box, this preset template for configuring Lima to work with Apptainer sets the file system in the Linux environment to read-only. In order to allow your Mac home directory to be writable from within the Linux environment, open the Lima configuration file located at `~/.lima/apptainer/lima.yaml` and add/edit the following lines under `mounts:`

```bash
mounts:
- location: "~"
  writable: true
```

In order for the changes to take effect, the VM needs to be stopped and then restarted:

```bash
limactl stop apptainer
limactl start apptainer
```

Finally, for accessing a shell environment in the VM to begin using Apptainer:

```bash
limactl shell apptainer
```

From inside this apptainer VM, it will now be possible to run the image (following step 3 below, once the image is obtained from step 2).

In order to exit the VM shell, simply type `exit`.

#### Installation on Linux

There are several different ways to install Apptainer on Linux, which are all described in the Apptainer documentation [here](https://apptainer.org/docs/admin/main/installation.html#installation-on-linux).

In particular, it can be installed from [pre-built packages](https://apptainer.org/docs/admin/main/installation.html#install-from-pre-built-packages) (e.g. for [Ubuntu](https://apptainer.org/docs/admin/main/installation.html#install-ubuntu-packages), the default distribution in WSL).

It can also be built and installed from source, by following the instructions in [INSTALL.md](https://github.com/apptainer/apptainer/blob/main/INSTALL.md) on GitHub.

### Step 2: Obtaining the Apptainer Image

#### Image Format (.sif)

Unlike Docker images which are published on Docker Hub, Apptainer uses the Singularity Image Format (SIF) for container images. These `.sif` files are fully encapsulated, single-file containers. This design is tailored for High Performance Computing (HPC) environments where simplicity and portability are crucial.

Each `.sif` file contains the entire container image, including its filesystem, metadata, and definition (like recipes or dependencies). The whole image is self-contained, allowing easy transfer and access across different systems without relying on runtime daemons (like Docker's `dockerd`) or complex architectures.

#### Download Image from Course GitHub Page

Navigate to the [releases page](https://github.com/anderkve/FYS3150/releases) for the FYS3150 repository in GitHub. There, you will see a list of the apptainer image versions, each with their own "assets". Click on the `.sif` file corresponding to the architecture of your machine in the name (either `x86` or `arm`) to download it.

Once the image (file ending in `.sif`) is downloaded, you should move it to a location where it's convenient to access it such as your home folder:
```
mv /path/to/downloads/folder/<name_of_image.sif> ~
```
**N.B.** - You can also put it directly in the folder where you're writing your code (the one under version control), but in this case it's advisable to add the image to the `.gitignore` list (see the description in the section on [gitignore](sec:gitignore) if you haven't set one up) so that it's not mistakenly added to your repository. Since the image is a few hundred MB in size, UiO GitHub will reject it being pushed to the server (similar to other large files that can be generated in the projects of the course).

### Step 3: Running the Image

To run an interactive session within the Apptainer container:

```bash
apptainer shell <name_of_image.sif>
```

Where `<name_of_image.sif>` is replaced by the name of the image that you downloaded in the previous step.

Upon running the container, your terminal should display a customized environment prompt within the container.

In order to exit the container, simply type `exit`.

## Accessing Files Outside the Container

By default, the container should provide you with an environment fully equipped to develop and run the code required for this course. However, the contents of the container are designed to be transient and will therefore be deleted once the container is removed.

In order to access or share files within your container, it is possible to "mount" directories from your file system, binding them to a directory from within the container.

By default, Apptainer already binds your home directory with the same path so that it's already available within the container.

> **N.B.** - this will be your Linux home directory (the one set up for you by WSL on Windows or by Lima on Mac)

Below are are the commands to mount additional directories when opening the container (e.g. your Mac home directory if you're on a Mac - this is less applicable to Windows users since the recommendation there that you're already working from your Linux home directory through WSL):

### Example with Bind Mount
```bash
apptainer shell --bind /path/on/host:/path/in/container fys3150_comp_phys_env_x86.sif
```
or for ARM architecture
```bash
apptainer shell --bind /path/on/host:/path/in/container fys3150_comp_phys_env_arm.sif
```

- **Replace** `/path/on/host` with the absolute path on your machine.
- **Replace** `/path/in/container` with where you want it mounted within the container.

## Support

The aim with these containers is to alleviate the various technical issues that are often encountered in this course by providing an environment that is more consistent across different platforms. That said, while the containerized workflow outlined above should remove most of the usual platform-specific technical issues, it should also (for the time being) be considered in the experimental phase of development. Therefore, any feedback on issues (or even just your experience) related to the containerized workflow are very much welcome via the [course discussion forum](https://github.uio.no/anderkve/FYS3150-forum/issues) or by direct email to the course instructors.

# Add a README and a gitignore

## README

Every repository should have a file `README.md` in its base directory. GitHub offers to create one when you register a new repo. Keep it short and up to date. It should explain how the repository is organised, and which commands to run to build and use your code.


(sec:gitignore)=
## gitignore

A `.gitignore` file lists the files Git should *not* track. GitHub also offers to create one from a template when you register a new repo.

### Why ignore files?

Git should only track the files you actually work on: source code, scripts and documentation. Typical files you do *not* want to track:

- **Compiled C++ files**, i.e. executables and object files like `main.o`. Anyone can regenerate these from the source code.
- **Python cache folders** (`__pycache__`), created by the Python interpreter when you run your code.
- **LaTeX auxiliary files** (`.aux`, `.log`, `.fls`, ...), generated when you compile your report.
- **Large data files.** Git becomes slow with large files, and GitHub rejects files larger than 100 MB. See also [Prevent the tracking of very large files](prevent_tracking_of_very_large_files.md).
- **Files with sensitive information**, e.g. configuration files containing passwords or tokens.

There is also a practical reason: `git status` lists every untracked file that is not covered by your gitignore. Without a gitignore, this list quickly becomes so cluttered that you overlook the files you *do* want to add:

![annoying](imgs/files_to_ignore.png)

### How to write a gitignore file

The file must be named `.gitignore` (no file extension) and placed in the root directory of your repository. The leading `.` makes it a hidden file, so you need `ls -a` to see it.

Each line in the file is a pattern. A pattern is either a specific file name, or uses the wildcard `*` to match several files. A gitignore file for the example above could look like this:

```
# Python cache files
__pycache__/

# Compiled C++ files
*.o
*.exe

# Data files
*.dat

# LaTeX auxiliary files
*.aux
*.fls
*.log
*.out
*.synctex.gz
*.fdb_latexmk

# Files with sensitive information
secrets.config
```

Add and commit the `.gitignore` file itself, so that everyone working on the repo shares the same rules.

Rather than writing the file from scratch, you can use a gitignore generator like [gitignore.io](https://www.toptal.com/developers/gitignore/). You tell it which tools you use, e.g. Linux, C++, Python and VSCode, and it generates a `.gitignore` that you copy into your repo and extend with your own patterns.

```{note}
A gitignore file only affects files that Git is not already tracking. If you have already committed a file that you want to ignore, first remove it from Git with `git rm --cached filename`, then commit.
```

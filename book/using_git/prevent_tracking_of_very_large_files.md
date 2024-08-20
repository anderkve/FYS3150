# Prevent the tracking of very large files

## Motivation

Due to the fact that Git keeps a history of every change made to files that it tracks, adding very large files can quickly lead to a bloated repository. This applies especially to binary files, although the same effect can happen with data files (e.g. CSV files storing intermediate results such as those that we encourage you to utilize for this course). Therefore, it's generally considered best practice not to add very large files to Git repositories in the first place.

```{note}
In this context, "very large" refers to sizes on the order of > 10 MB or so.
```

There is also a practical reason not to do so, which is that there's a hard cap on the file size (100 MB) beyond which GitHub won't allow files to be pushed to remote repositories on the server.

## Adding a pre-commit hook script

Using Git, it's possible to write arbitrary instructions that are executed each time certain actions are performed (so-called "hooks").
The following instructions (courtesy of ChatGPT) will allow you to automatically check the size of the files to be added in a commit and reject it if there is at least one file above a maximum size threshold.

First, navigate to your Git repository's `.git/hooks/` directory:
```sh
cd path/to/your/repo/.git/hooks/
```

Next, create a file named `pre-commit`:
```sh
touch pre-commit
```
and make it executable:
```sh
chmod +x pre-commit
```

Finally, edit the `pre-commit` file and add the following script:

```sh
#!/bin/bash

# Set the size limit in bytes (e.g., 5MB = 5242880 bytes)
MAX_SIZE=5242880

# Detect the operating system to use the correct stat syntax
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    STAT_CMD="stat -f%z"
else
    # Linux and other Unix-like systems
    STAT_CMD="stat -c%s"
fi

# Find files that exceed the size limit
large_files=$(git diff --cached --name-only --diff-filter=A | while read -r file; do
    if [ -f "$file" ]; then
        file_size=$($STAT_CMD "$file")
        if [ "$file_size" -gt "$MAX_SIZE" ]; then
            echo "$file"
        fi
    fi
done)

if [ -n "$large_files" ]; then
    echo "Error: The following files are larger than the allowed limit of $(($MAX_SIZE / 1024 / 1024))MB:"
    echo "$large_files"
    exit 1
fi

exit 0
```

And that's it! You should now be protected from committing very large files to your Git repository. To test if it works, generate a large file:
```sh
echo "This is a large file." > large_file.blob
# Simulate a large file by adding a lot of data
head -c 10M /dev/urandom > large_file.blob
```
and attempt to add + commit it:
```sh
git add large_file.blob
git commit -m "Test commit with a large file"
```

You should see a message like:
```
Error: The following files are larger than the allowed limit of 5MB:
large_file.blob
```

Don't forget to commit the `pre-commit` file itself to the repository once you've verified that it works!

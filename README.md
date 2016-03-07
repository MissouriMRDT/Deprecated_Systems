# Device Template for Energia
This repo contains a template for devices on the Energia platform. This is meant to be copied into a fresh repo before modification.

## Using this Template
1. To use this template, copy the .ino file to an empty folder.
2. To add the submodules, use the following commands:

  ```
git submodule add https://github.com/MST-MRDT/RoveWare.git libraries/RoveWare
git submodule add https://github.com/MST-MRDT/RoveBoard-Energia.git libraries/RoveBoard
```

3. Create an initial commit.

  ```
git commit -a -m "Initial Commit"
```

## Cloning a Derivative Repo
Any repo that uses submodules must be cloned with the command `git clone --recursive <url>`. This tells Git to recursively clone submodules in addition to the top-level repo.
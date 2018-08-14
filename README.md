<<<<<<< HEAD
# Deprecated-Systems
 Deprecated sub-system repositories that have no present day equivalent

How to add repos to this: 

1) Make branch on here for the repo you're about to copy in
2) Clone this repo onto your pc
3) Make sure that you've merged all branches on the deprecated repo into master, this process only preserves its master
4) in gitshell inside of the Deprecated-Systems folder:

git checkout [name of branch you're going to copy the repo into]

git remote add x [url of deprecated repo]

git fetch x

git merge x/master --allow-unrelated-histories

git remote rm x

5) delete old branch

=======
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

If you've already cloned the repo, use the command `git submodule update --init --recursive` to download the submodule data.
>>>>>>> x/master

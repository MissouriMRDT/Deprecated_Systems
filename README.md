# Deprecated-Systems
 Deprecated sub-system repositories that have no present day equivalent

How to add repos to this: 

1) Make branch on here for the repo you're about to copy in
2) Clone this repo onto your pc
3) Make sure that you've merged all branches on the deprecated repo into master, this process only preserves its master
4) in gitshell inside of the Deprecated-Systems folder:

git checkout **name of the branch you're copying the deprecated repo into**
git remote add **unique name for deprecated repo for this commit** **url of deprecated repo**
git fetch **unique name for deprecated repo for this commit**
git merge **unique name for deprecated repo for this commit**/master --allow-unrelated-histories

5) delete old branch

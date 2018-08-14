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
# RoveComm Wireshark Dissector
Custom dissector for Wireshark that parses and allows inspection of RoveComm protocol packets.

##Installing
1. Install Wireshark from www.wireshark.org.
2. Clone this repo to the Wireshark personal plugins directory. By default, on Windows this is `%APPDATA%\Wireshark\plugins` and on Linux is `~/.wireshark/plugins/`. Otherwise, check Wireshark > Help > About Wireshark > Folders > Personal Plugins.
3. After restarting Wireshark, RoveComm packets should be recognized in any capture files (including saved files).
>>>>>>> x/master

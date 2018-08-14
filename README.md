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
# MST-MRDT - [Science Station Software]

##  What is it?

[Science Station Software] is an all-encompassing program for use in the 
University Rover Challenge (URC) science task. It's designed for use with the 
RoveComm library and works alongside an arbitrary controlling base station. The
program aims to streamline the process of data collection,analysis, and 
presentation during the science task of URC.

##  The Latest Version

##  Documentation

##  Installation

##  Licensing

##  Contacts

If you want to be informed about new code releases and bug fixes, just watch 
the GitHub repository in which this document is contained.

If you want support for this program please contact John Maruska at 
jwmbq6@mst.edu

If you have a bug to report please email John Maruska at jwmbq6@mst.edu or post
a comment on the most recent commit to the master on GitHub.

If you want to participate in actively developing [Science Station Software] 
and are a student at Missouri S&T please consider joining the Mars Rover Design
Team! Check out the team on OrgSync and swing by the Student Design and 
Experiential Learning Center to talk with member.
>>>>>>> x/master

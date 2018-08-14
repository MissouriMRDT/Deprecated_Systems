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
<<<<<<< HEAD
# 2018 Development RoveComm2, individual branches for Python, C++ Wiring (Todo: WPF C#, Android SDK)

Supports:
sendTo all subscribers or sendTo specific ip address,
subscribe to all data_id's or subscribe to specific data_id's,
and generates the RoveDB column header for each packet (rover_id, board_id, session_count, data_sequence_count
=======
# 2018 Development RoveComm2 in Python 

Supports:  
sendTo all subscribers or sendTo specific ip address,   
subscribe to all data_id's or subscribe to specific data_id's,  
and generates the RoveDB column header for each packet (rover_id, board_id, session_count, data_sequence_count)
>>>>>>> origin/Python
>>>>>>> x/master

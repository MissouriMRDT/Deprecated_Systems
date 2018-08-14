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
# RoveComm-Software
Distributed Internet Protocol for Embedded Device 

#### About this Repo

This repository contains the RoveComm library, an example sketch for it's use,
and source files for a UDP client and server for testing messages send over the
RoveComm Protocol. The C folder has a readme of it's own that explains its usage.  

#### Installing the library
1. Open Energia
2. Select File -> Preferences
3. Change the sketchbook location to the .ino directory for the sketch you are
     working on. Click OK
4. Copy RoveComm_example/libraries/rovecomm to [sketchbook location]/libraries/
5. Restart Energia
6. Include these libraries in your sketch in order:
  - SPI.h
  - Ethernet.h
  - EthernetUdp.h
  - rovecomm.h
  

#### Communications Protocol
The bytes of the packet message are ordered like this:

| Version | Sequence # | Data ID | Data Size | Data      |
|:-------:|:----------:|:-------:|:---------:|:---------:|
| 1 Byte  | 2 Bytes    | 2 Bytes | 2 Bytes   | 0-N Bytes |

Version: Protocol Version  
Sequence #: For back and forth communication (currently unused)  
Data ID: Identification for data being transmitted  
Data Size: Number of bytes in the Data section  
Data: Raw data being transfered  
>>>>>>> x/master

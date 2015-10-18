# RoveComm-Software
Distributed Internet Protocol for Embedded Device 

Inside the C folder is a bit of C code for communicating with UDP so we only need one board. The energia folder has our communications template for communuicating on the TI boards.

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

# RoveComm Wireshark Dissector
Custom dissector for Wireshark that parses and allows inspection of RoveComm protocol packets.

##Installing
1. Install Wireshark from www.wireshark.org.
2. Clone this repo to the Wireshark personal plugins directory. By default, on Windows this is `%APPDATA%\Wireshark\plugins` and on Linux is `~/.wireshark/plugins/`. Otherwise, check Wireshark > Help > About Wireshark > Folders > Personal Plugins.
3. After restarting Wireshark, RoveComm packets should be recognized in any capture files (including saved files).

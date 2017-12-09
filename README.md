# DriveBoard-PR
Drives the Rover from a Raspberry Pi and a Wireless Xbox controller

# Setup
This will run on a raspberry pi with raspian wheezy or ubuntu 16.04.

1. Install raspbian on the raspberry pi and connect it to the internet
2. Install the Xbox controller driver
    sudo apt-get instal xboxdrv
3. Clone the repo to your raspberry pi
    git clone https://github.com/MST-MRDT/DriveBoard-PR.git
4. Mark the file as executable
    chmod +x DriveBoard-PR/xbox_remote_control.py

# Running

    python xbox_remote_control.py

After running this command
1) Your xbox controller should indicate a connection
2) Log information will be dumped to the console
3) Rovecomm messages will begin streaming to the drive board over UDP

Press `ctrl-c to exit`

# Enabling Autostart

Setting the program to run at startup is highly recommended.

Raspbian wheezy uses SystemD to control which programs run at startup.
SystemD is a bit of a pain, and unfortunately there's no easy way to put this
part in the repo.

1) Create the file `/etc/systemd/system/xbox_remote.service`

    [Unit]
    Description=Allows driving the rover through an Xbox controller
    After=multi-user.target
    After=network.target

    [Service]
    ExecStart=/home/pi/DriveBoard-PR/xbox_remote_control.py
    WorkingDirectory=/home/pi/DriveBoard-PR
    Type=idle
    Restart=always

    [Install]
    WantedBy=multi-user.target

2) Set the file permissions

    sudo chmod 644 /etc/systemd/system/xbox_remote.service

3) Enable the service

    sudo systemctl daemon-reload
    sudo systemctl enable xbox_remote.service
    sudo reboot

To view program output logs

    sudo systemctl status xbox_remote.service


# Credits

Written by Owen Chiaventone
Depends on work by Steven Jacobs. Attributions are in the relevant source files.
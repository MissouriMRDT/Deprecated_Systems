#!/usr/bin/python

import drivers.xbox
import drivers.motorsRoveComm
import time

THROTTLE_LIMIT =  40 # Percent
BOOST_SPEED    =  50 # Percent
UPDATE_RATE    = .01 # Seconds per update

x = drivers.xbox.Joystick()
motors = drivers.motorsRoveComm.Motors()

speed = 0
cruise_enabled = False
cruise_speed = 0

while True:
    speed = (x.rightTrigger() - x.leftTrigger()) * THROTTLE_LIMIT
    angle = 180 * x.leftX()

    if x.rightBumper():
        speed += BOOST_SPEED

    # A enables cruise control, B cancels.
    # Pumping the brakes immediately cancels cruise control
    if x.A():
        cruise_enabled = True
        cruise_speed = speed
    if x.B():
        cruise_enabled = False

    if cruise_enabled:
        if speed < 0:
            cruise_enabled = False

        if speed < cruise_speed:
            speed = cruise_speed

    motors.move(speed, angle)
    if speed != 0:
        print("Driving at speed %d, angle %d" % (speed, angle))
    time.sleep(UPDATE_RATE)


x.close()
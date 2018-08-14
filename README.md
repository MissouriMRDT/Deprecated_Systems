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
motor-controller
================

Brushless DC motor controller software with closed loop speed control.

All from Lukas Muller. I don't into code, so lets start looking at that.
A lookup table and his thermal analysis is also included.

Hardware -
* RevA is for the a 3-position hall effect encoder, which we won't have,
probably
* RevB is for a magnetic encoder, specifically [Avago
AEAT-6012](http://www.avagotech.com/pages/en/motion_control_encoder_products/magnetic_encoders/aeat-6012-a06/).
I don't know if this will fit, but we'll go with it.

Layout issues & things to improve (straight from the horse's mouth):

* More via at grounding points: More via are always better, but I know
we have a maximum set by Advanced Circuits so I didn't want to overdo
it.

* Fill top with ground pour?: There is a lot of space around the 3 phase
inverter (the FETS) where one could put copper for the ground on the top
side. Not sure if that would help though.

* Resistors on the data lines between gate drivers and 328P: The data
lines are pretty noisy due to the high pulse currents going below them.
In a 4 layer board one could separate the data line from the power by a
ground plane, but here that doesn't work. Small resistors (100Ohm) might
help as well, but there isn't a lot of room. I am not sure how noisy the
environment is. The switching frequency is not too high but we have some
sharp edges at turn on and turn off.
* ESD protection: I left 0603 spots on some data lines to add ESD diodes
if desired. It might be better if they were moved closer to the
connector though. Maybe move them on the bottom side of the board and
under the connector. Also the line driver doesn't have ESR right now.
The LTC490 is ok ESD wise. They also offer a driver with internal ESD
protection but that is probably a lot more expensive (the current driver
is already the most expensive part, maybe there is a cheaper
alternative). I don't know what your needs are so it might be fine as
long as you are careful when you handle it.

* The thermal resistor (changes resistance based on temperature) on the
bottom side (next to Q1) is meant to see if the board overheats. It is
connected right to the thermal pad of Q1 so it measures its temperature
really well. However, there is no info about the other switch
temperatures. Therefore, this only works if the switches experience a
somewhat similar load. In a 4 layer board we could put more of those
resistors in. Also the resistor is close to the LDO heat transfer path.
It is isolated by FR4 which is pretty bad thermal conductor in the
horizontal direction so it shouldn't mess up the reading too much. If
anything we get a worst case reading.

* There is still a lot of open space on the top and left hand side. I am
sure one could optimize the layout there a bit more if you want to make
the board 0.1-0.15 inches smaller.

--kawfey, 11-13-2014 4:03pm
>>>>>>> x/master

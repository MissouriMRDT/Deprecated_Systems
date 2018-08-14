import sys,tty,termios
import trexjr

motors = trexjr.TrexJr()

class _Getch:
    def __call__(self):
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(1)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch

def get():
        inkey = _Getch()
	prev = False
        while(1):
                k=inkey()
                if k!='':break
	if k == '\x1b': # Arrow Key
		k=inkey() # Arrow keys are thee characters
		k=inkey() # Clear out buffer
		speed = 110
	        if k=='A':
        	        print "up"
			motors.move(speed, speed)
	        elif k=='B':
	                print "down"
			motors.move(-speed, -speed)
	        elif k=='C':
	                print "right"
			speed = speed + 10
			motors.move(speed, -speed)
	        elif k=='D':
	                print "left"
			speed = speed + 10
			motors.move(-speed, speed)
        elif k == ' ': # Space
                print "space"
		motors.move(0, 0)
	elif k == '\x03': # Ctrl-C
		motors.move(0,0)
		quit()

def main():
	while True:
                get()
	motors.move(0,0)


if __name__=='__main__':
        main()

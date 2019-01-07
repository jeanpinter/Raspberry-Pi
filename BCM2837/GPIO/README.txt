To compile:  gcc -o gpio gpioMain.c gpioCtrl.c ../bcm2837.c

To run: sudo su -
        ./gpio

To stop: ^C
To turn off LEDs: ./gpio k

Future Improvement:
  1. Capture the kill signal and close the program properly
  2. Change to Object Oriented Program 

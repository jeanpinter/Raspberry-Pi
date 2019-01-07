#include <unistd.h>
#include "gpioCtrl.h"

/**
 * Purpose: blink two LEDs connected to GPIO 17 and GPIO 19
 */
int main(int argc, char *argv[])
{
	gpioInit();
	setGpioPinOps(19, GPIO_OUTPUT, 0);
	setGpioPinOps(17, GPIO_OUTPUT, 0);

	// run the program with argument 'k' to turn off the LED
	if (argc > 1)
	{
		// turn off the LEDs
		if (*argv[1] == 'k')
		{
			setGpioPinLevel(17, GPIO_LOW);
			setGpioPinLevel(19, GPIO_LOW);
		}
	}
	else
	{
		// TODO: capture the kill signal and reset
		while (1)
		{
			setGpioPinLevel(17, GPIO_HIGH);
			setGpioPinLevel(19, GPIO_LOW);
			sleep(2);
			setGpioPinLevel(17, GPIO_LOW);
			setGpioPinLevel(19, GPIO_HIGH);
			sleep(2);
		}
    }

}


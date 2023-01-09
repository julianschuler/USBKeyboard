/**************************************************************************
 *
 * File: CapsLockToggle.ino
 * Author: Julian Schuler (https://github.com/julianschuler)
 * License: GNU GPLv3, see LICENSE.txt
 * Description: This file is an example from the USBKeyboard library.
 *              It types in a message after hitting Caps Lock three times.
 *
 *************************************************************************/

#include <USBKeyboard.h>


/* currently available layouts: LAYOUT_US, LAYOUT_DE */
#define LAYOUT LAYOUT_US


/* create keyboard object mKeyboard */
USBKeyboard mKeyboard = USBKeyboard();


void setup() {
	/* USB timing has to be exact, therefore deactivate Timer0 interrupt */
	TIMSK0 = 0;

	/* initialize the keyboard */
	mKeyboard.begin()
}


void loop() {
	/* call this function at least every 20ms, otherwise an USB timeout will occur */
	mKeyboard.update();
	
	/* check if Caps Lock was toggled at least three times */
	if (mKeyboard.getCapsLockToggleCount() >= 3) {
		/* reset Caps Lock toggle counter */
		mKeyboard.resetCapsLockToggleCount();
		
		/* type in a custom message */
		mKeyboard.println("Hey, you have found Caps Lock on your keyboard!");
	}
	
	/* due to the deactivation of the Timer0 interrupt, delay()
	 * and millis() won't work, call delayMicroseconds() instead */
	delayMicroseconds(20000);
}

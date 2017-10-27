/**************************************************************************
 *
 * File: SendMultipleKeys.ino
 * Author: Julian Schuler (https://github.com/julianschuler)
 * License: GNU GPLv3, see LICENSE.txt
 * Description: This file is an example from the USBKeyboard library.
 *              It sends "Win+D" and "Win+E" (for Windows: show Desktop
 *              and open Explorer) after hitting Caps Lock three times.
 *
 *************************************************************************/

#include <USBKeyboard.h>


/* initialize class by creating object mKeyboard with US keyboard layout
 * currently available layouts: LAYOUT_US, LAYOUT_DE */
USBKeyboard mKeyboard = USBKeyboard(LAYOUT_US);


void setup() {
	/* USB timing has to be exact, therefore deactivate Timer0 interrupt */
	TIMSK0 = 0;
}


void loop() {
	/* call this function at least every 20ms, otherwise an USB timeout will occur */
	mKeyboard.update();
	
	/* check if Caps Lock was toggled at least three times */
	if (mKeyboard.getCapsLockToggleCount() >= 3) {
		/* reset Caps Lock toggle counter */
		mKeyboard.resetCapsLockToggleCount();
		
		/* send the E and D keys together with the GUI key (for Windows: Win key)
		 * available modifiers: CONTROL, SHIFT, ALT, GUI */
		mKeyboard.sendKeys(mKeyboard.asciiToKeycode('D'), mKeyboard.asciiToKeycode('E'), 0, 0, 0, 0, GUI);
	}
	
	/* due to the deactivation of the Timer0 interrupt, delay()
	 * and millis() won't work, call delayMicroseconds() instead */
	delayMicroseconds(20000);
}

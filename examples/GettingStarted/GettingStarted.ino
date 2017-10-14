/**************************************************************************
 *
 * File: GettingStarted.ino
 * Author: Julian Schuler (https://github.com/julianschuler)
 * License: GNU GPLv3, see LICENSE.txt
 * Description: This file is an example from the USBKeyboard library.
 *              It types in a message after pressing a button and shows
 *              the state of Caps Lock with the internal LED.
 *
 **************************************************************************/

#include <USBKeyboard.h>

/* connect a button to this pin and GND */
#define BUTTON_PIN 7

/* initialize class by creating object mKeyboard with US keyboard layout
 * currently available layouts: LAYOUT_US, LAYOUT_DE */
USBKeyboard mKeyboard = USBKeyboard(LAYOUT_US);

bool lastButtonState = HIGH;
bool lastCapsLockState;


void setup() {
	/* USB timing has to be exact, therefore deactivate Timer0 interrupt */
	TIMSK0 = 0;
	
	/* set the button pin as input and activate the internal pullup resistor */
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	
	/* set the internal LED pin (normally D13) as output */
	pinMode(LED_BUILTIN, OUTPUT);
	
	/* set the internal LED corresponding to the Caps Lock state */
	if (mKeyboard.isCapsLockActivated()) {
		digitalWrite(LED_BUILTIN, HIGH);
		lastCapsLockState = HIGH;
	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
		lastCapsLockState = LOW;
	}
}


void loop() {
	/* call this function at least every 20ms, otherwise an USB timeout will occur */
	mKeyboard.update();
	
	/* check if button is pressed */
	if (digitalRead(BUTTON_PIN) == LOW) {
		if (lastButtonState == HIGH) {
			/* print() and println() can be used to type in chars, Strings
			 * and numbers, similar to Serial.print() and Serial.println() */
			mKeyboard.println("Hello World!");
			lastButtonState = LOW;
		}
	}
	else if (lastButtonState == LOW) {
		lastButtonState = HIGH;
	}
			
	/* check if the Caps Lock state has changed */
	if (mKeyboard.isCapsLockActivated() != lastCapsLockState) {
		/* toggle lastCapsLockState */
		lastCapsLockState = !lastCapsLockState;
		
		/* toggle LED state */
		digitalWrite(LED_BUILTIN, lastCapsLockState);
	}
	
	/* due to the deactivation of the Timer0 interrupt, delay()
	 * and millis() won't work, call delayMicroseconds() instead */
	delayMicroseconds(20000);
}

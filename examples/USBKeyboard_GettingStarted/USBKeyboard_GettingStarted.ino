#include <USBKeyboard.h>

#define BUTTON_PIN 7

/* initialize class by creating object mKeyboard */
USBKeyboard mKeyboard = USBKeyboard();

bool lastState = LOW;


void setup() {
	/* USB timing has to be exact, therefore deactivate Timer0 interrupt */
	TIMSK0 = 0;
	
	/* set the button pin as input and activate the internal pullup resistor */
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() {
	/* call this function at least every 20ms, otherwise an USB timeout will occur */
	mKeyboard.update();
	
	/* check if button is pressed */
	if (digitalRead(BUTTON_PIN) == LOW) {
		if (lastState == HIGH) {
			/* print() and println() can be used to type in chars, Strings
			 * and numbers, similar to Serial.print() and Serial.println() */
			mKeyboard.println("Hello World!");
			lastState = LOW;
			
			/* get the state of Caps Lock */
			if (mKeyboard.isCapsLockActivated()) {
				mKeyboard.print("Caps Lock is activated: ");
			}
			else {
				mKeyboard.print("Caps Lock is deactivated: ");
			}
			
			/* igore the state of Caps Lock to show whether Caps Lock is activated or not*/
			mKeyboard.write('a', true);
			
			/* compensate the state of Caps Lock, as in print() and println() */
			mKeyboard.write('\n');
		}
	}
	else if (lastState == LOW) {
		lastState = HIGH;
	}
	
	/* due to the deactivation of the Timer0 interrupt, delay()
	 * and millis() won't work, call delayMicroseconds() instead */
	delayMicroseconds(20000);
}

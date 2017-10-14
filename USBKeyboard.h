/**********************************************************************************************
 * 
 * This library for the Arduino IDE adds HID USB keyboard functionality to your projects, it
 * allows Arduinos and other AVRs to act as an HID USB Device. This way no drivers have to be
 * installed, the keyboard will work with every PC and OS.
 * It is based the V-USB code by Objective Developement (https://www.obdev.at/products/vusb/)
 * and under the same license (GNU GPLv3, see LICENSE.txt).
 * 
 *********************************************************************************************/

#ifndef __USBKeyboard_h__
#define __USBKeyboard_h__

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>
#include <usbdrv.h>
#include <Arduino.h>

/* constants */
#define LAYOUT_US 	0
#define LAYOUT_DE 	1

#define CONTROL		(1<<0)
#define SHIFT 		(1<<1)
#define ALT 		(1<<2)
#define GUI			(1<<3)


/* global variables */
static uint8_t idle_rate = 500 / 4; /* see HID1_11.pdf sect 7.2.4 */
static uint8_t protocol_version = 0; /* see HID1_11.pdf sect 7.2.6 */
volatile static uint8_t LED_states = 0; /* see HID1_11.pdf appendix B section 1 */
volatile static uint8_t toggle_counter = 0; /* keep track of how many times caps lock have toggled */
static uint8_t keyboard_layout = LAYOUT_US; /* keyboard layout, US layout by standard */


class USBKeyboard : public Print {
public: /*#################### PUBLIC FUNCTIONS ####################*/
	/*******************************************************
	 * Constructor, call it when initializing the library
	 ******************************************************/
	USBKeyboard();
	USBKeyboard(uint8_t layout);
	
	
	/*******************************************************
	 * Call this function at least every 20ms,
	 * otherwise an USB timeout will occur
	 ******************************************************/
	void update();
	
	
	/*******************************************************
	 * Type a single char to the USB host
	 ******************************************************/
	virtual size_t write(uint8_t ascii) {sendKey(asciiToKeycode(ascii), asciiToShiftState(ascii));}
	
	
	/*******************************************************
	 * Send a single key to the USB host
	 ******************************************************/
	void sendKey(uint8_t keycode) {sendKey(keycode, 0);}
	void sendKey(uint8_t keycode, uint8_t modifiers);
	
	
	/*******************************************************
	 * Send up to 6 keys to the USB host
	 ******************************************************/
	void sendKeys(uint8_t keycode1, uint8_t keycode2, uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, uint8_t keycode6) {sendKeys(keycode1, keycode2, keycode3, keycode4, keycode5, keycode6, 0);}
	void sendKeys(uint8_t keycode1, uint8_t keycode2, uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, uint8_t keycode6, uint8_t modifiers);
	
	
	/*******************************************************
	 * Translate ASCII char to keycode
	 ******************************************************/
	uint8_t asciiToKeycode(char ascii);
	
	
	/*******************************************************
	 * Translate ASCII char to Shift state, taking into
	 * consideration the status of Caps Lock
	 ******************************************************/
	uint8_t asciiToShiftState(char ascii);
	
	
	/*******************************************************
	 * Get the state of Caps Lock
	 ******************************************************/
	bool isCapsLockActivated();
	
	
	/*******************************************************
	 * Get how often Caps Lock was toggled
	 ******************************************************/
	uint8_t getCapsLockToggleCount();
	
	
	/*******************************************************
	 * Reset the Caps Lock toggle counter
	 ******************************************************/
	void resetCapsLockToggleCount();
	
	
private: /*################### PRIVATE FUNCTIONS ###################*/
	/*******************************************************
	 * Send the keyboard report
	 ******************************************************/
	void sendReport(uint8_t modifiers, uint8_t keycode1, uint8_t keycode2, uint8_t keycode3, uint8_t keycode4, uint8_t keycode5, uint8_t keycode6);
};

#endif /* __USBKeyboard_h__ */

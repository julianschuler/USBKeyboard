/*********************************************************************************************
 * 
 * This library adds USB keyboard functionality for the Arduino IDE, so Arduinos and and other AVRs 
 * It is based the V-USB code by Objective Developement (https://www.obdev.at/products/vusb/) and under 
 * the same license (GNU v3, see LICENSE.txt).
 * 
 *********************************************************************/

#ifndef __USBKeyboard_h__
#define __USBKeyboard_h__

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>
#include <usbdrv.h>
#include <Arduino.h>

/* change it to 1, if you usually use a Keyboard with an US layout*/
#define US_LAYOUT 0


/* global variables */
static uint8_t modifier = 0x00;
static uint8_t idle_rate = 500 / 4; // see HID1_11.pdf sect 7.2.4
static uint8_t protocol_version = 0; // see HID1_11.pdf sect 7.2.6
static uint8_t LED_state = 0; // see HID1_11.pdf appendix B section 1
static uint8_t blink_count = 0; // keep track of how many times caps lock have toggled


class USBKeyboard : public Print {
public: /*#################### PUBLIC FUNCTIONS ####################*/
	/*******************************************************
	 * constructor, call it when initializing the library
	 ******************************************************/
	USBKeyboard();
	
	
	/*******************************************************
	 * Call this function at least every 20ms,
	 * otherwise an USB timeout will occur
	 ******************************************************/
	void update();
	
	
	/*******************************************************
	 * Type a single char to the USB host
	 ******************************************************/
	virtual size_t write(uint8_t ascii) {write(ascii, false);}
	//void write(char ascii) {write(ascii, false);}
	void write(char ascii, bool ignoreCapsLock);
	
	
private: /*################### PRIVATE FUNCTIONS ###################*/
	/*******************************************************
	 * Translate ASCII to appropriate keyboard report,
	 * taking into consideration the status of caps lock
	 ******************************************************/
	uint8_t ASCII_to_keycode(char ascii, bool ignoreCapsLock);
	
	
	/*******************************************************
	 * send the keyboard report
	 ******************************************************/
	void send_report(uint8_t keycode);
};

#endif // __USBKeyboard_h__

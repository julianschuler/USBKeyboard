/**********************************************************************
 * 
 * This is the C++ part of the USBKeyboard library.
 * See USBKeyboard.h and the example files for a full documentation.
 * 
 *********************************************************************/

#include <USBKeyboard.h>


/* set USB HID report descriptor for boot protocol keyboard */
PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
	0x05, 0x01,					// USAGE_PAGE (Generic Desktop)
	0x09, 0x06,					// USAGE (Keyboard)
	0xa1, 0x01,					// COLLECTION (Application)
	0x75, 0x01,					//   REPORT_SIZE (1)
	0x95, 0x08,					//   REPORT_COUNT (8)
	0x05, 0x07,					//   USAGE_PAGE (Keyboard)(Key Codes)
	0x19, 0xe0,					//   USAGE_MINIMUM (Keyboard LeftControl)(224)
	0x29, 0xe7,					//   USAGE_MAXIMUM (Keyboard Right GUI)(231)
	0x15, 0x00,					//   LOGICAL_MINIMUM (0)
	0x25, 0x01,					//   LOGICAL_MAXIMUM (1)
	0x81, 0x02,					//   INPUT (Data,Var,Abs) ; Modifier byte
	0x95, 0x01,					//   REPORT_COUNT (1)
	0x75, 0x08,					//   REPORT_SIZE (8)
	0x81, 0x03,					//   INPUT (Cnst,Var,Abs) ; Reserved byte
	0x95, 0x05,					//   REPORT_COUNT (5)
	0x75, 0x01,					//   REPORT_SIZE (1)
	0x05, 0x08,					//   USAGE_PAGE (LEDs)
	0x19, 0x01,					//   USAGE_MINIMUM (Num Lock)
	0x29, 0x05,					//   USAGE_MAXIMUM (Kana)
	0x91, 0x02,					//   OUTPUT (Data,Var,Abs) ; LED report
	0x95, 0x01,					//   REPORT_COUNT (1)
	0x75, 0x03,					//   REPORT_SIZE (3)
	0x91, 0x03,					//   OUTPUT (Cnst,Var,Abs) ; LED report padding
	0x95, 0x06,					//   REPORT_COUNT (6)
	0x75, 0x08,					//   REPORT_SIZE (8)
	0x15, 0x00,					//   LOGICAL_MINIMUM (0)
	0x25, 0x65,					//   LOGICAL_MAXIMUM (101)
	0x05, 0x07,					//   USAGE_PAGE (Keyboard)(Key Codes)
	0x19, 0x00,					//   USAGE_MINIMUM (Reserved (no event indicated))(0)
	0x29, 0x65,					//   USAGE_MAXIMUM (Keyboard Application)(101)
	0x81, 0x00,					//   INPUT (Data,Ary,Abs)
	0xc0						// END_COLLECTION
};



/* constructor */
USBKeyboard::USBKeyboard () {
	cli();
	USBOUT &= ~USBMASK;
	USBDDR &= ~USBMASK;
	TIMSK0 = 0;
	usbDeviceDisconnect();
	delayMicroseconds(250000);
	usbDeviceConnect();
	usbInit();
	sei();
}


/* make usbPoll() accessable within the library */
void USBKeyboard::update() {
	usbPoll();
}


/* write single char */
void USBKeyboard::write(char ascii, bool ignoreCapsLock) {
	USBKeyboard::send_report(USBKeyboard::ASCII_to_keycode(ascii, ignoreCapsLock));
	modifier = 0x00;
	USBKeyboard::send_report(0x00);
}


/* translate ASCII char to keyboard report */
uint8_t USBKeyboard::ASCII_to_keycode(char ascii, bool ignoreCapsLock) {
	uint8_t keycode = 0x00; //default value, if char is not found
	modifier = (_BV(1) & LED_state); // invert shift if Caps Lock is activated
	
	if (ascii >= 'A' && ascii <= 'Z') {
		keycode = 0x04 + ascii - 'A'; // set letter
		modifier ^= _BV(1); // hold shift
	}
	else if (ascii >= 'a' && ascii <= 'z') {
		keycode = 0x04 + ascii - 'a'; // set letter
	}
	else if (ascii >= '0' && ascii <= '9') {
		if (ascii == '0') {
			keycode = 0x27;
		}
		else {
			keycode = 0x1E + ascii - '1'; 
		}
	}
	else {
		switch (ascii) {
			case '!':
				modifier ^= _BV(1); // hold shift
				keycode = 0x1E;
				break;
			case '@':
				modifier ^= _BV(1); // hold shift
				keycode = 0x1F;
				break;
			case '#':
				modifier ^= _BV(1); // hold shift
				keycode = 0x20;
				break;
			case '$':
				modifier ^= _BV(1); // hold shift
				keycode = 0x21;
				break;
			case '%':
				modifier ^= _BV(1); // hold shift
				keycode = 0x22;
				break;
			case '^':
				modifier ^= _BV(1); // hold shift
				keycode = 0x23;
				break;
			case '&':
				modifier ^= _BV(1); // hold shift
				keycode = 0x24;
				break;
			case '*':
				modifier ^= _BV(1); // hold shift
				keycode = 0x25;
				break;
			case '(':
				modifier ^= _BV(1); // hold shift
				keycode = 0x26;
				break;
			case ')':
				modifier ^= _BV(1); // hold shift
				keycode = 0x27;
				break;
			case '~':
				modifier ^= _BV(1); // hold shift
				// fall through
			case '`':
				keycode = 0x35;
				break;
			case '_':
				modifier ^= _BV(1); // hold shift
				// fall through
			case '-':
				keycode = 0x2D;
				break;
			case '+':
				modifier ^= _BV(1); // hold shift
				// fall through
			case '=':
				keycode = 0x2E;
				break;
			case '{':
				modifier ^= _BV(1); // hold shift
				// fall through
			case '[':
				keycode = 0x2F;
				break;
			case '}':
				modifier ^= _BV(1); // hold shift
				// fall through
			case ']':
				keycode = 0x30;
				break;
			case '|':
				modifier = _BV(1); // hold shift
				// fall through
			case '\\':
				keycode = 0x31;
				break;
			case ':':
				modifier = _BV(1); // hold shift
				// fall through
			case ';':
				keycode = 0x33;
				break;
			case '"':
				modifier = _BV(1); // hold shift
				// fall through
			case '\'':
				keycode = 0x34;
				break;
			case '<':
				modifier = _BV(1); // hold shift
				// fall through
			case ',':
				keycode = 0x36;
				break;
			case '>':
				modifier ^= _BV(1); // hold shift
				// fall through
			case '.':
				keycode = 0x37;
				break;
			case '?':
				modifier ^= _BV(1); // hold shift
				// fall through
			case '/':
				keycode = 0x38;
				break;
			case ' ':
				keycode = 0x2C;
				break;
			case '\t':
				keycode = 0x2B;
				break;
			case '\n':
				keycode = 0x28;
				break;
		}
	}
	return keycode;
}


/* send the keyoard report */
void USBKeyboard::send_report(uint8_t keycode) {
	// perform usb background tasks until the report can be sent, then send it
	while (!usbInterruptIsReady()) usbPoll();
	uint8_t report_buffer[8] = {modifier, 0, keycode, 0, 0, 0, 0, 0};
	if (keycode == 0x28) {
		report_buffer[2] = 0x2C;
		report_buffer[3] = 0x2A;
		while (!usbInterruptIsReady()) usbPoll();
		usbSetInterrupt(report_buffer, sizeof(report_buffer));
		report_buffer[2] = 0x00;
		report_buffer[3] = 0x00;
		while (!usbInterruptIsReady()) usbPoll();
		usbSetInterrupt(report_buffer, sizeof(report_buffer));
		report_buffer[2] = keycode;
	}
	usbSetInterrupt(report_buffer, sizeof(report_buffer)); // send
	// see http://vusb.wikidot.com/driver-api
}


/* declare the USB device as HID keyboard */
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
	// see HID1_11.pdf sect 7.2 and http://vusb.wikidot.com/driver-api
	usbRequest_t *rq = (void *)data;

	if ((rq->bmRequestType & USBRQ_TYPE_MASK) != USBRQ_TYPE_CLASS)
		return 0; // ignore request if it's not a class specific request

	// see HID1_11.pdf sect 7.2
	switch (rq->bRequest) {
		case USBRQ_HID_GET_IDLE:
			usbMsgPtr = &idle_rate; // send data starting from this byte
			return 1; // send 1 byte
		case USBRQ_HID_SET_IDLE:
			idle_rate = rq->wValue.bytes[1]; // read in idle rate
			return 0; // send nothing
		case USBRQ_HID_GET_PROTOCOL:
			usbMsgPtr = &protocol_version; // send data starting from this byte
			return 1; // send 1 byte
		case USBRQ_HID_SET_PROTOCOL:
			protocol_version = rq->wValue.bytes[1];
			return 0; // send nothing
		case USBRQ_HID_SET_REPORT:
			if (rq->wLength.word == 1) { // check data is available
				// 1 byte, we don't check report type (it can only be output or feature)
				// we never implemented "feature" reports so it can't be feature
				// so assume "output" reports
				// this means set LED status
				// since it's the only one in the descriptor
				return USB_NO_MSG; // send nothing but call usbFunctionWrite
			}
			else { // no data or do not understand data, ignore
				return 0; // send nothing
			}
		default: // do not understand data, ignore
			return 0; // send nothing
	}
}


/* detect LED states (Caps Lock, Num Lock, Scroll Lcok) */
usbMsgLen_t usbFunctionWrite(uint8_t * data, uchar len) { 
	if (data[0] == LED_state)
		return 1;
	else
		LED_state = data[0];
	
	return 1; // Data read, not expecting more
}

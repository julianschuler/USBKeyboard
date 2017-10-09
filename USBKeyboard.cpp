/**********************************************************************
 * 
 * This is the C++ part of the USBKeyboard library.
 * See USBKeyboard.h and the example files for a full documentation.
 * 
 *********************************************************************/

#include <USBKeyboard.h>


/* set USB HID report descriptor for boot protocol keyboard */
PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
	0x05, 0x01,			/* USAGE_PAGE (Generic Desktop)						*/
	0x09, 0x06,			/* USAGE (Keyboard)									*/
	0xa1, 0x01,			/* COLLECTION (Application)							*/
	0x75, 0x01,			/* REPORT_SIZE (1)									*/
	0x95, 0x08,			/* REPORT_COUNT (8)									*/
	0x05, 0x07,			/* USAGE_PAGE (Keyboard)(Key Codes)					*/
	0x19, 0xe0,			/* USAGE_MINIMUM (Keyboard LeftControl)(224)		*/
	0x29, 0xe7,			/* USAGE_MAXIMUM (Keyboard Right GUI)(231)			*/
	0x15, 0x00,			/* LOGICAL_MINIMUM (0)								*/
	0x25, 0x01,			/* LOGICAL_MAXIMUM (1)								*/
	0x81, 0x02,			/* INPUT (Data,Var,Abs) ; Modifier byte				*/
	0x95, 0x01,			/* REPORT_COUNT (1)									*/
	0x75, 0x08,			/* REPORT_SIZE (8)									*/
	0x81, 0x03,			/* INPUT (Cnst,Var,Abs) ; Reserved byte				*/
	0x95, 0x05,			/* REPORT_COUNT (5)									*/
	0x75, 0x01,			/* REPORT_SIZE (1)									*/
	0x05, 0x08,			/* USAGE_PAGE (LEDs)								*/
	0x19, 0x01,			/* USAGE_MINIMUM (Num Lock)							*/
	0x29, 0x05,			/* USAGE_MAXIMUM (Kana)								*/
	0x91, 0x02,			/* OUTPUT (Data,Var,Abs) ; LED report				*/
	0x95, 0x01,			/* REPORT_COUNT (1)									*/
	0x75, 0x03,			/* REPORT_SIZE (3)									*/
	0x91, 0x03,			/* OUTPUT (Cnst,Var,Abs) ; LED report padding		*/
	0x95, 0x06,			/* REPORT_COUNT (6)									*/
	0x75, 0x08,			/* REPORT_SIZE (8)									*/
	0x15, 0x00,			/* LOGICAL_MINIMUM (0)								*/
	0x25, 0x65,			/* LOGICAL_MAXIMUM (101)							*/
	0x05, 0x07,			/* USAGE_PAGE (Keyboard)(Key Codes)					*/
	0x19, 0x00,			/* USAGE_MINIMUM (Reserved (no event indicated))(0)	*/
	0x29, 0x65,			/* USAGE_MAXIMUM (Keyboard Application)(101)		*/
	0x81, 0x00,			/* INPUT (Data,Ary,Abs)								*/
	0xc0				/*  END_COLLECTION									*/
};


const uint8_t US_keycodes[96] = {
	0x2C,			// Space
	0x1E,			// !
	0x34,			// "
	0x20,			// #
	0x21,			// $
	0x22,			// %
	0x24,			// &
	0x34,			// '
	0x26,			// (
	0x27,			// )
	0x25,			// *
	0x2E,			// +
	0x36,			// ,
	0x2D,			// -
	0x37,			// .
	0x38,			// /
	0x27,			// 0
	0x1E,			// 1
	0x1F,			// 2
	0x20,			// 3
	0x21,			// 4
	0x22,			// 5
	0x23,			// 6
	0x24,			// 7
	0x25,			// 8
	0x26,			// 9
	0x33,			// :
	0x33,			// ;
	0x36,			// <
	0x2E,			// =
	0x37,			// >
	0x38,			// ?
	0x1F,			// @
	0x04,			// A
	0x05,			// B
	0x06,			// C
	0x07,			// D
	0x08,			// E
	0x09,			// F
	0x0A,			// G
	0x0B,			// H
	0x0C,			// I
	0x0D,			// J
	0x0E,			// K
	0x0F,			// L
	0x10,			// M
	0x11,			// N
	0x12,			// O
	0x13,			// P
	0x14,			// Q
	0x15,			// R
	0x16,			// S
	0x17,			// T
	0x18,			// U
	0x19,			// V
	0x1A,			// W
	0x1B,			// X
	0x1C,			// Y
	0x1D,			// Z
	0x2F,			// [
	0x31,			//'\'
	0x30,			// ]
	0x23,			// ^
	0x2D,			// _
	0xC0,			// `
	0x04,			// a
	0x05,			// b
	0x06,			// c
	0x07,			// d
	0x08,			// e
	0x09,			// f
	0x0A,			// g
	0x0B,			// h
	0x0C,			// i
	0x0D,			// j
	0x0E,			// k
	0x0F,			// l
	0x10,			// m
	0x11,			// n
	0x12,			// o
	0x13,			// p
	0x14,			// q
	0x15,			// r
	0x16,			// s
	0x17,			// t
	0x18,			// u
	0x19,			// v
	0x1A,			// w
	0x1B,			// x
	0x1C,			// y
	0x1D,			// z
	0x2F,			// {
	0x31,			// |
	0x30,			// }
	0xC0			// ~
};


const char US_modifiers_shift[12] = {
	// Bit number:			1	2	3	4	5	6	7	8
	// --------------------------------------------------
	B01111111,		//	Space	!	"	#	$	%	&	'
	B11110000,		//		(	)	*	+	,	-	.	/
	B00000000,		//		0	1	2	3	4	5	6	7
	B00101010,		//		8	9	:	;	<	=	>	?
	B11111111,		//		@	A	B	C	D	E	F	G
	B11111111,		//		H	I	J	K	L	M	N	O
	B11111111,		//		P	Q	R	S	T	U	V	W
	B11100011,		//		X	Y	Z	[	\	]	^	_
	B00000000,		//		`	a	b	c	d	e	f	g
	B00000000,		//		h	i	j	k	l	m	n	o
	B00000000,		//		p	q	r	s	t	u	v	w
	B00011110		//		x	y	z	{	|	}	~
};


/*##################################### PUBLIC FUNCTIONS #####################################*/

/* constructor */
USBKeyboard::USBKeyboard () {
	cli();
	USBOUT &= ~USBMASK;
	USBDDR &= ~USBMASK;
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


bool USBKeyboard::isCapsLockActivated() {
	 return (LED_states & 2);
}


uint8_t USBKeyboard::getCapsLockToggleCount() {
	return toggle_counter;
}


void USBKeyboard::resetCapsLockToggleCount() {
	toggle_counter = 0;
}


/*#################################### PRIVATE FUNCTIONS #####################################*/

/* translate ASCII char to keyboard report */
uint8_t USBKeyboard::ASCII_to_keycode(char ascii, bool ignoreCapsLock) {
	/* check if input is ASCII char and translate it to keycode */
	if (ascii >= ' ' && ascii <= '~') {
		/* set shift depending on the Caps Lock state and input char */
		modifier = !ignoreCapsLock << 1 & LED_states ^ ((US_modifiers_shift[ascii/8 - 4] >> (7 - ((ascii - 32) % 8))) << 1 & 2);
		return US_keycodes[ascii - 32];
	}
	
	/* translate \t and \n */
	if (ascii == '\t') return 0x2B;
	if (ascii == '\n') return 0x28;
	
	/* char unknown */
	return 0;
}


/* send the keyoard report */
void USBKeyboard::send_report(uint8_t keycode) {
	/* perform usb background tasks until the report can be sent, then send it */
	while (!usbInterruptIsReady()) usbPoll();
	uint8_t report_buffer[8] = {modifier, 0, keycode, 0, 0, 0, 0, 0};
	if (keycode == 0x28) {
		report_buffer[2] = 0x2C;
		report_buffer[3] = 0x2A;
		report_buffer[4] = 0x28;
	}
	usbSetInterrupt(report_buffer, sizeof(report_buffer)); /* send */
	/* see http://vusb.wikidot.com/driver-api */
}


/* declare the USB device as HID keyboard */
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
	/* see HID1_11.pdf sect 7.2 and http://vusb.wikidot.com/driver-api */
	usbRequest_t *rq = (void *)data;
	
	if ((rq->bmRequestType & USBRQ_TYPE_MASK) != USBRQ_TYPE_CLASS)
		return 0; /* ignore request if it's not a class specific request */
	
	/* see HID1_11.pdf sect 7.2 */
	switch (rq->bRequest) {
		case USBRQ_HID_GET_IDLE:
			usbMsgPtr = &idle_rate; /* send data starting from this byte */
			return 1; /* send 1 byte */
		case USBRQ_HID_SET_IDLE:
			idle_rate = rq->wValue.bytes[1]; /* read in idle rate */
			return 0; /* send nothing */
		case USBRQ_HID_GET_PROTOCOL:
			usbMsgPtr = &protocol_version; /* send data starting from this byte */
			return 1; /* send 1 byte */
		case USBRQ_HID_SET_PROTOCOL:
			protocol_version = rq->wValue.bytes[1];
			return 0; /* send nothing */
		case USBRQ_HID_SET_REPORT:
			if (rq->wLength.word == 1) { /* check data is available
				1 byte, we don't check report type (it can only be output or feature)
				we never implemented "feature" reports so it can't be feature
				so assume "output" reports
				this means set LED status
				since it's the only one in the descriptor */
				return USB_NO_MSG; /* send nothing but call usbFunctionWrite */
			}
		default: /* do not understand data, ignore */
			return 0; /* send nothing */
	}
}


/* detect LED states (Caps Lock, Num Lock, Scroll Lcok) */
usbMsgLen_t usbFunctionWrite(uint8_t* data, uchar len) {
	if (data[0] == LED_states) /* return, if no LED states have changed */
		return 1;
	if (data[0] ^ LED_states & 2) /* increase counter, if Caps Lock state changed */
		toggle_counter++;
	LED_states = data[0];
	return 1; /* Data read, not expecting more */
}

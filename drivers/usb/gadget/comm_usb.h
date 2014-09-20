


/*
 * Processing for UI of USB event header
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/

#ifndef	__USB_GADGET_COMM_USB_H
#define	__USB_GADGET_COMM_USB_H

#define TYPE_REQUEST_OPEN		0x00000001	
#define TYPE_REQUEST_CLOSE		0x00000002	
#define TYPE_REQUEST_READ		0x00000003	
#define TYPE_REQUEST_CONNECT		0x00000004	
#define TYPE_REQUEST_DISCONNECT		0x00000005	

#define TYPE_RESPONSE_OPEN		0x00000001	
#define TYPE_RESPONSE_CLOSE		0x00000002	
#define TYPE_RESPONSE_READ		0x00000003	
#define TYPE_RESPONSE_CONNECT		0x00000004	
#define TYPE_RESPONSE_DISCONNECT	0x00000005	

#define USBMODE_IDLE			0x00000000	
#define USBMODE_MASS			0x00000001	
#define USBMODE_MTP			0x00000002	
#define USBMODE_MODEM			0x00000003	
#define USBMODE_CDROM			0x00000004	

#define USBMODE_IPOVERUSB		0x00000005	
#define USBMODE_TETHERING		0x00000006	


#define STATUS_SUCCESS			0		
#define STATUS_FAILURE			-1		

#define USB_REPLY_MAXSIZE		(10*1024)	




struct usb_comm_header {
	u32	size;					
	u32	type;					
};




struct usb_comm_request_body_connect {
	u32	boot;					
};




struct usb_comm_request_body_open {
	u32	mode;					
};




struct usb_comm_request_body_close {
	u32	mode;					
};




struct usb_comm_request_body_read {
	u32	offset;					
	u32	size;					
	u32	concat;					
	u32	total;					
};




struct usb_comm_request {
	
	struct usb_comm_header				head;	
	union {
		
		struct usb_comm_request_body_connect	connect;	

		
		struct usb_comm_request_body_open	open;	

		
		struct usb_comm_request_body_close	close;	

		
		struct usb_comm_request_body_read	read;	
	} body;
};




struct usb_comm_response_body_open {
	u32	filesize;				
};




struct usb_comm_response_body_read_concat {
	u32	bodysize;				
	u32	concat;					
	u32	total;					
	u32	size;					
};




struct usb_comm_response_body_read {
	u32	bodysize;				
	u32	size;					
	u8	data[64*1024];				
};




struct usb_comm_response {
	
	struct usb_comm_header				head;	
	u32						status;
	union {
		
		struct usb_comm_response_body_open	open;	

		
		struct usb_comm_response_body_read	read;	
	} body;
};

extern int comm_usb_init(void (* pcb_func)(struct usb_comm_response *, void *), void *puser);
extern void comm_usb_fin(void);

extern void comm_usb_end(void);

extern int comm_usb_request(struct usb_comm_request * request);
extern int comm_usb_request_connect(u32 boot);
extern int comm_usb_request_open(u32 mode);
extern int comm_usb_request_close(u32 mode);
extern int comm_usb_request_disconnect(void);
extern int comm_usb_request_read(u32 offset, u32 size);


extern int comm_usb_cdrom_interruptible(void);



extern int comm_usb_is_connect_polling(void);


#endif 




/*
  HID.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef HID_h
#define HID_h

#include <stdint.h>
#include <Arduino.h>

#if defined(USBCON)

//================================================================================
//================================================================================
//  HID 'Driver'

#define HID_GET_REPORT        0x01
#define HID_GET_IDLE          0x02
#define HID_GET_PROTOCOL      0x03
#define HID_SET_REPORT        0x09
#define HID_SET_IDLE          0x0A
#define HID_SET_PROTOCOL      0x0B

#define HID_HID_DESCRIPTOR_TYPE         0x21
#define HID_REPORT_DESCRIPTOR_TYPE      0x22
#define HID_PHYSICAL_DESCRIPTOR_TYPE    0x23

class HID_
{
public:
  HID_(void);
  int begin(void);
};

int8_t   HID_Plug(void);
int   HID_GetInterface(u8* interfaceNum);
int   HID_GetDescriptor(int8_t t);
bool  HID_Setup(Setup& setup, u8 i);
void  HID_SendReport(uint8_t id, const void* data, int len);

extern HID_ HID;

typedef struct
{
  u8 len;     // 9
  u8 dtype;   // 0x21
  u8 addr;
  u8  versionL; // 0x101
  u8  versionH; // 0x101
  u8  country;
  u8  desctype; // 0x22 report
  u8  descLenL;
  u8  descLenH;
} HIDDescDescriptor;

typedef struct 
{
  InterfaceDescriptor     hid;
  HIDDescDescriptor     desc;
  EndpointDescriptor      in;
} HIDDescriptor;

#define HID_TX HID_ENDPOINT_INT

#define D_HIDREPORT(_descriptorLength) \
  { 9, 0x21, 0x1, 0x1, 0, 1, 0x22, _descriptorLength, 0 }

extern const u8 _hidReportDescriptor[] PROGMEM;

// MUST be declared by the module
size_t getsizeof_hidReportDescriptor();

#define WEAK __attribute__ ((weak))

#endif

#endif
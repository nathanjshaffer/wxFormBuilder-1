#ifndef LANGUAGE_PNG_H
#define LANGUAGE_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char language_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 
	0xF3, 0xFF, 0x61, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 
	0x41, 0x00, 0x00, 0xAF, 0xC8, 0x37, 0x05, 0x8A, 0xE9, 0x00, 
	0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 0x66, 
	0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x41, 0x64, 0x6F, 0x62, 
	0x65, 0x20, 0x49, 0x6D, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 
	0x64, 0x79, 0x71, 0xC9, 0x65, 0x3C, 0x00, 0x00, 0x01, 0xBF, 
	0x49, 0x44, 0x41, 0x54, 0x38, 0xCB, 0x8D, 0x92, 0xBD, 0x4F, 
	0xC2, 0x50, 0x14, 0xC5, 0x59, 0x4D, 0x4C, 0x9C, 0xDC, 0x8C, 
	0x89, 0x83, 0x89, 0x83, 0x8B, 0xCE, 0xFE, 0x1B, 0x26, 0x2E, 
	0xEA, 0xA0, 0x7F, 0x81, 0xC6, 0x5D, 0x17, 0x19, 0x24, 0x24, 
	0xCE, 0xBA, 0xA8, 0x93, 0x06, 0x48, 0xD4, 0x41, 0xC4, 0x3C, 
	0xE2, 0x80, 0x93, 0x11, 0x43, 0x58, 0xD0, 0xE0, 0x47, 0x10, 
	0xF9, 0x28, 0x15, 0x28, 0x1F, 0x85, 0xB6, 0xE2, 0xF5, 0xDC, 
	0x47, 0x49, 0xC4, 0xD0, 0xEA, 0xF0, 0x4B, 0xFB, 0x5E, 0xEF, 
	0x39, 0xEF, 0xDE, 0xD3, 0xE7, 0x59, 0xF0, 0x86, 0xA7, 0x80, 
	0x1F, 0x9C, 0x3A, 0x70, 0x0C, 0x56, 0xC0, 0x38, 0x11, 0x79, 
	0x7E, 0xE3, 0xC1, 0x87, 0xDD, 0x68, 0x22, 0x2B, 0x6A, 0xBA, 
	0x29, 0xB4, 0x1E, 0xCD, 0x2E, 0x55, 0x50, 0xAC, 0xEA, 0x22, 
	0x18, 0x4B, 0x0B, 0xD4, 0x6D, 0x3A, 0x19, 0x9C, 0xB1, 0xB8, 
	0x82, 0xE2, 0x72, 0xC3, 0x14, 0x1F, 0x75, 0x53, 0x94, 0xEA, 
	0x86, 0x28, 0xD5, 0x0C, 0x51, 0xD4, 0xDA, 0x72, 0x3F, 0xA3, 
	0xD4, 0xD9, 0xE0, 0xD0, 0xD1, 0x80, 0x4F, 0x65, 0xB1, 0x62, 
	0x8B, 0x0A, 0xD5, 0xB6, 0xC8, 0x55, 0x5A, 0x22, 0x5B, 0x6E, 
	0xC9, 0xF5, 0x5F, 0x06, 0xE7, 0xB5, 0x96, 0x29, 0x54, 0x9C, 
	0xCC, 0xC5, 0x79, 0x88, 0xAF, 0x93, 0xB9, 0xDB, 0xF5, 0xBD, 
	0x58, 0x79, 0xC9, 0x77, 0x65, 0x2D, 0x03, 0x7E, 0xA2, 0xCE, 
	0x00, 0x15, 0x9B, 0x2C, 0xD8, 0xE6, 0xFC, 0xD8, 0x20, 0xA0, 
	0x42, 0x68, 0x58, 0x1D, 0x29, 0xE6, 0x93, 0x37, 0xF6, 0x6F, 
	0xAA, 0xC8, 0x85, 0x30, 0x1A, 0x69, 0x3D, 0x9A, 0x5D, 0x90, 
	0x0B, 0x21, 0x17, 0x42, 0x2E, 0x04, 0x6D, 0x90, 0x0D, 0x56, 
	0x7D, 0x81, 0xB8, 0x88, 0xA7, 0x15, 0x61, 0x7E, 0x76, 0x24, 
	0x8B, 0x3B, 0x11, 0x8B, 0xC5, 0x98, 0x9F, 0x30, 0x1A, 0x21, 
	0x17, 0x42, 0x2E, 0x84, 0x5C, 0x08, 0x5D, 0xCA, 0x7D, 0x8C, 
	0xC5, 0x06, 0x8F, 0x72, 0x0E, 0xBC, 0xCC, 0x81, 0x13, 0x4E, 
	0xFC, 0xF2, 0x2E, 0xC3, 0xF3, 0x5A, 0x7C, 0x2A, 0x8B, 0x15, 
	0x5B, 0x84, 0x5C, 0x08, 0xDD, 0x11, 0x72, 0x91, 0xEB, 0x3E, 
	0x03, 0xDB, 0xE4, 0x20, 0x12, 0x97, 0xE2, 0x30, 0xA8, 0x23, 
	0x17, 0x42, 0x2E, 0xB2, 0x38, 0xFF, 0x43, 0x9C, 0x51, 0x75, 
	0xCA, 0xE3, 0xFD, 0x5D, 0x6D, 0xB0, 0xC1, 0x4B, 0x4F, 0x3C, 
	0xC4, 0x61, 0x82, 0x0B, 0x30, 0x09, 0x0A, 0xC8, 0x85, 0xDA, 
	0x56, 0xA7, 0x4F, 0xCC, 0x5D, 0x28, 0xD8, 0x47, 0x5E, 0xF4, 
	0x5A, 0xAC, 0xB1, 0x41, 0xAA, 0x67, 0x30, 0x0A, 0xB6, 0xC0, 
	0x84, 0xBD, 0xF6, 0xFA, 0x43, 0xF7, 0x94, 0x78, 0x2E, 0x11, 
	0x32, 0x91, 0xB0, 0xD9, 0x5B, 0xA9, 0x41, 0x4F, 0x79, 0x8D, 
	0x8E, 0xA2, 0x29, 0x16, 0xEB, 0x60, 0xCD, 0x33, 0xE8, 0xDF, 
	0xDA, 0x26, 0xF3, 0x40, 0xD3, 0x74, 0x83, 0x90, 0x0B, 0x0B, 
	0xBE, 0x40, 0x1A, 0x24, 0xF9, 0xF6, 0x82, 0x11, 0x79, 0x0F, 
	0x9C, 0x0C, 0x6C, 0x93, 0x07, 0xE4, 0xC2, 0xE2, 0x36, 0x98, 
	0x19, 0x78, 0x91, 0x5C, 0xC4, 0xC3, 0xDC, 0x01, 0x68, 0x81, 
	0x59, 0xA7, 0x3A, 0x37, 0x83, 0x31, 0x10, 0x02, 0xD3, 0x6E, 
	0x5D, 0xBA, 0x8E, 0xF0, 0x1F, 0xBE, 0x01, 0xC1, 0x9F, 0x09, 
	0x94, 0x7A, 0xD3, 0x3C, 0xB7, 0x00, 0x00, 0x00, 0x00, 0x49, 
	0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& language_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( language_png, sizeof( language_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //LANGUAGE_PNG_H
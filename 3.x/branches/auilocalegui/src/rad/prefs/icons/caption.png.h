#ifndef CAPTION_PNG_H
#define CAPTION_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char caption_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 
	0xF3, 0xFF, 0x61, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 
	0x42, 0x00, 0xAE, 0xCE, 0x1C, 0xE9, 0x00, 0x00, 0x00, 0x06, 
	0x62, 0x4B, 0x47, 0x44, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 
	0xA0, 0xBD, 0xA7, 0x93, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 
	0x59, 0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B, 0x13, 
	0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00, 0x00, 0x07, 0x74, 
	0x49, 0x4D, 0x45, 0x07, 0xDB, 0x07, 0x05, 0x08, 0x1A, 0x33, 
	0x30, 0x3D, 0xA0, 0x1B, 0x00, 0x00, 0x01, 0xE8, 0x49, 0x44, 
	0x41, 0x54, 0x38, 0xCB, 0xA5, 0x93, 0x3F, 0x68, 0x54, 0x41, 
	0x10, 0xC6, 0x7F, 0x77, 0xF7, 0x8C, 0x17, 0x93, 0x13, 0x54, 
	0xB0, 0x8A, 0x24, 0xFE, 0x6B, 0x4C, 0x27, 0x08, 0x92, 0xD4, 
	0x29, 0xD3, 0x58, 0xD8, 0x2A, 0x28, 0x16, 0x16, 0x49, 0x23, 
	0x29, 0xD4, 0x46, 0x51, 0xB1, 0x48, 0xA7, 0x9D, 0x89, 0xAD, 
	0xA8, 0x8D, 0x60, 0xA3, 0x60, 0x11, 0x82, 0x90, 0x4A, 0x4F, 
	0x45, 0xB0, 0x11, 0x12, 0xAB, 0xA8, 0xE1, 0xD4, 0x40, 0xEE, 
	0xEE, 0xBD, 0xDD, 0xF9, 0x63, 0xF1, 0xEE, 0x9E, 0x9E, 0x17, 
	0xAB, 0x2C, 0x0C, 0x3B, 0xEC, 0xB7, 0xF3, 0xCD, 0x7C, 0x33, 
	0xBB, 0x25, 0x77, 0x67, 0x27, 0x2B, 0x59, 0x7D, 0x30, 0xB3, 
	0x5C, 0x4E, 0x06, 0x4E, 0x4A, 0xF3, 0xD7, 0x90, 0x9B, 0x82, 
	0x19, 0x6E, 0x9A, 0xA3, 0xDE, 0xF1, 0xDD, 0x70, 0x89, 0xB8, 
	0x69, 0x6E, 0x12, 0xA9, 0x0C, 0xD6, 0x9A, 0x16, 0x5A, 0x6F, 
	0x13, 0x60, 0x72, 0xDF, 0xA9, 0xE9, 0x72, 0x73, 0xED, 0x3D, 
	0xDA, 0xDC, 0xDC, 0x36, 0xCB, 0xEE, 0x83, 0xA3, 0x64, 0xDF, 
	0xBF, 0x14, 0xFB, 0xC8, 0xAB, 0x65, 0xBE, 0x9E, 0x99, 0x1A, 
	0x6A, 0xBC, 0x7E, 0x3C, 0x59, 0xFA, 0x7C, 0xEF, 0x82, 0xBB, 
	0xC4, 0x3C, 0x4B, 0x57, 0x8E, 0x09, 0xEE, 0x8E, 0xAB, 0x82, 
	0x09, 0x26, 0x21, 0xC7, 0x55, 0xFB, 0x2A, 0x4A, 0x5C, 0x22, 
	0xD9, 0xD4, 0xDC, 0xB6, 0x99, 0x9F, 0x6F, 0x3D, 0x01, 0x83, 
	0xE9, 0xBD, 0x67, 0x8B, 0xB3, 0xBF, 0x7B, 0xE6, 0x0F, 0xCF, 
	0x91, 0xE0, 0xC6, 0xF8, 0xF8, 0x78, 0x5F, 0xF0, 0xFC, 0xBB, 
	0x9B, 0x94, 0xCA, 0xA0, 0x28, 0xCF, 0x36, 0x1F, 0x71, 0x6D, 
	0xE2, 0x56, 0xDF, 0x9D, 0x0F, 0x2A, 0x94, 0xBB, 0x8C, 0x66, 
	0x86, 0x99, 0x11, 0x24, 0x70, 0xE7, 0xCD, 0x75, 0x24, 0x46, 
	0x46, 0x87, 0xC7, 0x18, 0x1B, 0x3E, 0x4C, 0x16, 0x53, 0xE6, 
	0x5E, 0xCC, 0xD0, 0x6C, 0x37, 0x49, 0xD3, 0x94, 0x56, 0xAB, 
	0x05, 0x40, 0x50, 0xA3, 0x8C, 0x5B, 0x0F, 0xEB, 0xE2, 0xA7, 
	0xFB, 0x34, 0xB6, 0x36, 0x10, 0x51, 0xC4, 0x04, 0x71, 0x61, 
	0xB0, 0xB2, 0x87, 0xF5, 0x9F, 0xEB, 0xCC, 0x2F, 0xDD, 0x46, 
	0x55, 0x31, 0xCB, 0x63, 0xC4, 0x20, 0x29, 0x46, 0xD6, 0x59, 
	0x97, 0x4E, 0xCC, 0xE2, 0xEE, 0x5C, 0x7E, 0x79, 0x9E, 0x91, 
	0xE1, 0x43, 0xA8, 0x19, 0xAB, 0xDF, 0xD6, 0xB8, 0x32, 0x71, 
	0x95, 0xA3, 0x07, 0x8E, 0x17, 0xC1, 0x00, 0xD1, 0x9C, 0xC4, 
	0x55, 0x8B, 0xE6, 0x74, 0xCD, 0xCC, 0x08, 0x59, 0x24, 0xAA, 
	0x62, 0xAE, 0x6C, 0xFC, 0xD8, 0xE0, 0xC8, 0xFE, 0x63, 0xFC, 
	0xFB, 0xE8, 0xD4, 0x9C, 0x04, 0x93, 0x9E, 0x1E, 0xFC, 0x21, 
	0x08, 0x44, 0x8D, 0x98, 0x2B, 0x21, 0x0D, 0xDB, 0x4E, 0x49, 
	0xCD, 0x49, 0x4C, 0x72, 0xB0, 0xAB, 0xAD, 0x5B, 0x45, 0x48, 
	0x03, 0x62, 0x82, 0xBA, 0x92, 0xFD, 0x87, 0x20, 0x9A, 0x93, 
	0xA0, 0x79, 0x05, 0xD5, 0x6A, 0xB5, 0x07, 0xCC, 0xDA, 0x91, 
	0xE5, 0x8F, 0x4B, 0x64, 0xED, 0x48, 0x48, 0x03, 0xB5, 0x5A, 
	0xAD, 0x8F, 0xC0, 0xBC, 0xD3, 0xC4, 0x7A, 0xBD, 0x4E, 0xB5, 
	0x5A, 0x2D, 0x64, 0x98, 0x19, 0x37, 0x4E, 0xDF, 0xED, 0x91, 
	0xB4, 0xB2, 0xB2, 0x52, 0xF8, 0xEE, 0x4E, 0xA3, 0xD1, 0x60, 
	0x97, 0x3B, 0x09, 0xB0, 0x30, 0xF0, 0x74, 0xF6, 0xA2, 0xC4, 
	0x90, 0x3F, 0x61, 0x89, 0x98, 0x3B, 0xA2, 0x8E, 0x9A, 0x23, 
	0x9E, 0x6B, 0xB5, 0xCE, 0xAE, 0x9E, 0xFB, 0x95, 0x1C, 0x5B, 
	0x28, 0xED, 0xF4, 0x3B, 0xFF, 0x06, 0xD7, 0x41, 0x8C, 0x72, 
	0xDF, 0xCA, 0x5B, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 
	0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& caption_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( caption_png, sizeof( caption_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //CAPTION_PNG_H

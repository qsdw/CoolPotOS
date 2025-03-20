#include "krlibc.h"
#include "video.h"

uint32_t dwidth, dheight;
uint32_t c_width, c_height; // 字符绘制总宽高
int32_t  dx, dy;
int32_t  cx, cy; // 字符坐标
uint32_t dcolor, dback_color;

uint32_t volatile *dscreen;

uint8_t bafont[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x44, 0x82, 0xaa, 0xaa, 0x82, 0x82, 0xaa, 0x92, 0x44, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x7c, 0xfe, 0xd6, 0xd6, 0xfe, 0xfe, 0xd6, 0xee, 0x7c, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x6c, 0xfe, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x54, 0xfe, 0x54, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0xd6, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc3, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0x42, 0x42, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x99, 0xbd, 0xbd, 0x99, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x10, 0x38, 0x54, 0x92, 0x10, 0x10, 0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x10, 0x10, 0xfe, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x0c, 0x0e, 0x0b, 0x0b, 0x0a, 0x08, 0x08, 0x18, 0x78, 0xf8, 0x70, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1f, 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x77, 0xff, 0x66, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x54, 0x38, 0x28, 0x38, 0x54, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x02, 0x06, 0x0e, 0x1e, 0x3e, 0x7e, 0xfe, 0x7e, 0x3e, 0x1e, 0x0e, 0x06, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x38, 0x54, 0x92, 0x10, 0x10, 0x10, 0x92, 0x54, 0x38, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x44, 0x44, 0x00, 0x00,
    0x00, 0x3e, 0x4a, 0x8a, 0x8a, 0x8a, 0x8a, 0x4a, 0x3a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x00, 0x00,
    0x7c, 0x82, 0x40, 0x20, 0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x08, 0x04, 0x82, 0x7c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x38, 0x54, 0x92, 0x10, 0x10, 0x10, 0x92, 0x54, 0x38, 0x10, 0x7c, 0x00, 0x00,
    0x00, 0x10, 0x38, 0x54, 0x92, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x92, 0x54, 0x38, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0xfe, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x40, 0xfe, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xfe, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x44, 0xfe, 0x44, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x38, 0x38, 0x7c, 0x7c, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x7c, 0x7c, 0x38, 0x38, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x66, 0x66, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0xfe, 0x44, 0x44, 0xfe, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x7c, 0x92, 0x92, 0x50, 0x38, 0x14, 0x92, 0x92, 0x7c, 0x10, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x92, 0x96, 0x6c, 0x18, 0x30, 0x6c, 0xd2, 0x92, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x38, 0x20, 0x76, 0x88, 0x88, 0x88, 0x76, 0x00, 0x00, 0x00,
    0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0c, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x18, 0xff, 0x18, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x8e, 0x9a, 0xb2, 0xa2, 0xc2, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x08, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0xc2, 0x82, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x02, 0x02, 0x3c, 0x02, 0x02, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0c, 0x14, 0x24, 0x44, 0x84, 0x84, 0xfe, 0x04, 0x04, 0x1e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfe, 0x80, 0x80, 0x80, 0xfc, 0x02, 0x02, 0x02, 0xc2, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x80, 0x80, 0xfc, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfe, 0x82, 0x82, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x7e, 0x02, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x02, 0x04, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x9d, 0xa5, 0xa5, 0xad, 0xb6, 0x40, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfc, 0x42, 0x42, 0x42, 0x7c, 0x42, 0x42, 0x42, 0x42, 0xfc, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x80, 0x80, 0x80, 0x80, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfc, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0xfc, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfe, 0x42, 0x40, 0x40, 0x78, 0x78, 0x40, 0x40, 0x42, 0xfe, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfe, 0x42, 0x40, 0x48, 0x78, 0x48, 0x40, 0x40, 0x40, 0xf0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x80, 0x80, 0x8e, 0x82, 0x82, 0x82, 0x7e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc2, 0x42, 0x42, 0x42, 0x44, 0x78, 0x44, 0x42, 0x42, 0xc2, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x42, 0xfe, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x81, 0xc3, 0xa5, 0x99, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x82, 0x82, 0xc2, 0xa2, 0x92, 0x8a, 0x86, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfc, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x40, 0xf0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x92, 0x8a, 0x7c, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfc, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x44, 0x44, 0x42, 0xe2, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x40, 0x38, 0x04, 0x02, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfe, 0x92, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x99, 0xa5, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x81, 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81, 0x81, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x44, 0x38, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xff, 0x81, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x41, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x28, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00,
    0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x04, 0x7c, 0x84, 0x84, 0x84, 0x8c, 0x72, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x80, 0x80, 0x80, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1c, 0x04, 0x04, 0x7c, 0x84, 0x84, 0x84, 0x84, 0x8c, 0x76, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0xfe, 0x80, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1c, 0x22, 0x20, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x84, 0x84, 0x84, 0x84, 0x84, 0x7c, 0x04, 0x84, 0x78,
    0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x5c, 0x66, 0x42, 0x42, 0x42, 0x42, 0xc2, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x42, 0x42, 0x3c,
    0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x42, 0x44, 0x48, 0x78, 0x44, 0x42, 0xc2, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xa5, 0x99, 0x81, 0x81, 0x81, 0x81, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0xe0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x84, 0x84, 0x84, 0x84, 0x84, 0x7c, 0x04, 0x04, 0x0e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x62, 0x40, 0x40, 0x40, 0x40, 0xe0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x60, 0x18, 0x04, 0x82, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x7e, 0x10, 0x10, 0x10, 0x10, 0x12, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x7a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0x81, 0x99, 0xa5, 0xc3, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x42, 0x24, 0x18, 0x24, 0x42, 0x81, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x6c, 0x10, 0x20, 0x40, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x84, 0x08, 0x10, 0x20, 0x42, 0xfe, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0e, 0x10, 0x10, 0x10, 0x60, 0x10, 0x10, 0x10, 0x10, 0x0e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x70, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x08, 0x08, 0x70, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x72, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x44, 0x82, 0xfe, 0x82, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x44, 0x82, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x82, 0x44, 0x38, 0x10, 0x20,
    0x00, 0x00, 0x24, 0x24, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x42, 0x3e, 0x00, 0x00,
    0x0c, 0x08, 0x10, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0xfe, 0x80, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x10, 0x28, 0x44, 0x00, 0x78, 0x04, 0x04, 0x3c, 0x44, 0x84, 0x84, 0x44, 0x3e, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x24, 0x00, 0x78, 0x04, 0x04, 0x3c, 0x44, 0x84, 0x84, 0x44, 0x3e, 0x00, 0x00,
    0x10, 0x08, 0x04, 0x00, 0x00, 0x78, 0x04, 0x04, 0x3c, 0x44, 0x84, 0x84, 0x44, 0x3e, 0x00, 0x00,
    0x00, 0x18, 0x24, 0x18, 0x00, 0x78, 0x04, 0x04, 0x3c, 0x44, 0x84, 0x84, 0x44, 0x3e, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x80, 0x80, 0x80, 0x80, 0x80, 0x42, 0x3c, 0x08, 0x10,
    0x00, 0x10, 0x28, 0x44, 0x00, 0x38, 0x44, 0x82, 0x82, 0xfe, 0x80, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x24, 0x00, 0x38, 0x44, 0x82, 0x82, 0xfe, 0x80, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x10, 0x08, 0x04, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0xfe, 0x80, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x24, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x10, 0x28, 0x44, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x10, 0x08, 0x04, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x24, 0x24, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00,
    0x00, 0x38, 0x44, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00,
    0x0c, 0x08, 0x10, 0xfe, 0x80, 0x80, 0x80, 0x80, 0xf8, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x1c, 0x12, 0x72, 0x9e, 0x90, 0x90, 0x92, 0x6c, 0x00, 0x00,
    0x0c, 0x10, 0x20, 0x28, 0x28, 0x28, 0xfe, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x00, 0x00,
    0x00, 0x10, 0x28, 0x44, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x24, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x10, 0x08, 0x04, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x10, 0x28, 0x44, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x42, 0x3e, 0x00, 0x00,
    0x10, 0x08, 0x04, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x42, 0x3e, 0x00, 0x00,
    0x00, 0x00, 0x24, 0x24, 0x00, 0x82, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x20, 0x20, 0x40,
    0x24, 0x24, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x24, 0x24, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x28, 0x28, 0x28, 0x3c, 0x6a, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0x6a, 0x3c, 0x28, 0x28, 0x28,
    0x00, 0x0c, 0x12, 0x20, 0x20, 0x20, 0xfc, 0x20, 0x20, 0x20, 0x60, 0xa0, 0xb2, 0x4c, 0x00, 0x00,
    0x00, 0x82, 0x82, 0x44, 0x28, 0x10, 0xfe, 0x10, 0x10, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x00, 0xe0, 0x90, 0x88, 0x88, 0x88, 0x94, 0xe4, 0x9f, 0x84, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00,
    0x00, 0x0c, 0x12, 0x10, 0x10, 0x10, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00, 0x00,
    0x0c, 0x08, 0x10, 0x00, 0x00, 0x78, 0x04, 0x04, 0x3c, 0x44, 0x84, 0x84, 0x44, 0x3e, 0x00, 0x00,
    0x0c, 0x08, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x0c, 0x08, 0x10, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x0c, 0x08, 0x10, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x42, 0x3e, 0x00, 0x00,
    0x00, 0x12, 0x2a, 0x24, 0x00, 0xf8, 0x84, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00,
    0x12, 0x2a, 0x24, 0x00, 0x82, 0xc2, 0xc2, 0xa2, 0x92, 0x92, 0x8a, 0x86, 0x86, 0x82, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x78, 0x04, 0x04, 0x3c, 0x44, 0x84, 0x84, 0x44, 0x3e, 0x00, 0xfe, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0xfe, 0x00, 0x00,
    0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x02, 0x02, 0x02, 0x00, 0x00,
    0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x00, 0xfe, 0x00, 0x78, 0x04, 0x38, 0x40, 0x7c, 0x00, 0x00,
    0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x00, 0xfe, 0x00, 0x18, 0x28, 0x48, 0x7c, 0x08, 0x00, 0x00,
    0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x12, 0x24, 0x48, 0x90, 0x90, 0x48, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x90, 0x48, 0x24, 0x12, 0x12, 0x24, 0x48, 0x90, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44,
    0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa,
    0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x10, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4, 0x04, 0xf4, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x04, 0xf4, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4, 0x04, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x17, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x17, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf7, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xf7, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x17, 0x10, 0x17, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf7, 0x00, 0xf7, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf7, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xff, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static void copy_char(uint32_t *vram, int off_x, int off_y, int x, int y, int x1, int y1,
                      int xsize) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            vram[(y + i + off_y) * xsize + (j + x + off_x)] =
                vram[(y1 + i + off_y) * xsize + (j + x1 + off_x)];
        }
    }
}

void default_scroll() {
    if (cx > c_width) {
        cx = 0;
        cy++;
    } else
        cx++;

    if (cy >= c_height) {
        cy = c_height - 1;

        memcpy((void *)dscreen, (void *)dscreen + dwidth * 16 * sizeof(uint32_t),
               dwidth * (dheight - 16) * sizeof(uint32_t));
        for (int i = (dwidth * (dheight - 16)); i != (dwidth * dheight); i++) {
            dscreen[i] = dback_color;
        }
    }
}

void default_draw_char(char c, int32_t x, int32_t y) {
    if (c == ' ') { return; }

    uint8_t *font = bafont;
    // uint8_t *font = ascfont;

    font += c * 16;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 9; j++) {
            if (font[i] & (0x80 >> j)) { dscreen[(y + i) * dwidth + x + j] = dcolor; }
        }
    }
}

void draw_rect(int x0, int y0, int x1, int y1, int c) {
    int x, y;

    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            (dscreen)[y * dwidth + x] = c;
        }
    }
}

void default_putchar(char ch) {
    if (ch == '\n') {
        cx = 0;
        cy++;
        return;
    } else if (ch == '\r') {
        cx = 0;
        return;
    } else if (ch == '\t') {
        default_putchar(' ');
        return;
    } else if (ch == '\b' && cx > 0) {
        cx -= 1;
        if (cx == 0) {
            cx = c_width - 1;
            if (cy != 0) cy -= 1;
            if (cy == 0) cx = 0, cy = 0;
        }
        int x = (cx + 1) * 9 - 7;
        int y = cy * 16;
        draw_rect(x, y, x + 9, y + 16, dback_color);
        return;
    }
    default_scroll();
    default_draw_char(ch, cx * 9 - 7, cy * 16);
}

void default_write(const char *data, size_t size) {
    static const long hextable[] = {
        [0 ... 255] = -1, ['0'] = 0, 1,  2,  3,  4, 5, 6, 7, 8, 9, ['A'] = 10, 11, 12, 13, 14, 15,
        ['a'] = 10,       11,        12, 13, 14, 15};

    for (; *data; ++data) {
        char c = *data;
        if (c == '\033') {
            uint32_t text_color = 0;
            ++data;
            while (*data && text_color >= 0) {
                text_color = (text_color << 4) | hextable[*data++];
                if (*data == ';') break;
            }
            dcolor = text_color;
        } else if (c == '\034') {
            uint32_t text_color = 0, a = 0;
            ++data;
            while (*data && text_color >= 0) {
                text_color = (text_color << 4) | hextable[*data++];
                if (*data == ';') break;
            }
            dback_color = text_color;
        } else
            default_putchar(c);
    }
}

void default_writestring(const char *data) {
    default_write(data, strlen(data));
}

void default_terminal_setup() {
    dwidth      = get_vbe_width();
    dheight     = get_vbe_height();
    dscreen     = get_vbe_screen();
    dcolor      = 0xc6c6c6;
    dback_color = 0x000000;
    c_width     = dwidth / 9;
    c_height    = dheight / 16;
}
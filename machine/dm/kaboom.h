#ifndef _KABOOM_H
#define _KABOOM_H


#define bucket_width 16
#define bucket_height 3
static U8 bucket_bits[] = { bucket_width, bucket_height,
  0xFF, 0xFF,
  0x09, 0x90,
  0xFF, 0xFF,
  };


#define bomb_width  4
#define bomb_height 5
static const U8 bomb_bits[] = { bomb_width, bomb_height,
	  0x2,
	  0xE,
	  0xF,
	  0xF,
	  0x6,
};
	


#define splash_width  8
#define splash_height 4
static const U8 splash_bits[] = { splash_width, splash_height,
	  0x18,
	  0x00,
	  0x2B,
	  0x03,
};


#define bomber_width  16
#define bomber_height 5
static const U8 bomber_bits[] = { bomber_width, bomber_height,
		0x00, 0x00,
		0xAA, 0xAA,
		0x3C, 0xC3,
		0xFF, 0xFF,
		0x3C, 0xC3,
};


#endif

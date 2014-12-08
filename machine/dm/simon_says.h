#ifndef _SISAY_H
#define _SISAY_H



#define left_arrow_width 8
#define left_arrow_height 5
static U8 left_arrow_bits[] = { left_arrow_width, left_arrow_height,
  0x10,
  0x3F,
  0x7F,
  0x3F,
  0x10,
  };


#define right_arrow_width 8
#define right_arrow_height 5
static U8 right_arrow_bits[] = { right_arrow_width, right_arrow_height,
  0x08,
  0xFc,
  0xFE,
  0xFC,
  0x08,
  };



#endif

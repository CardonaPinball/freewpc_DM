
/****************************************************************************
 * circle 1
 ****************************************************************************/

#define circle1_1_low_width 24
#define circle1_1_low_height 22
static U8 circle1_1_low_bits[] = { circle1_1_low_width , circle1_1_low_height,
		0x00, 0x3F, 0x00, //         ######
		0xC0, 0xFF, 0x00, //       ##########
		0xF0, 0xC7, 0x07, //     #######   #####
		0xF8, 0x00, 0x07, //    #####        ###
		0xF8, 0x38, 0x06, //    #####   ###   ##
		0x7C, 0xFC, 0x1D, //   #####   ####### ###
		0x3E, 0xC6, 0x19, //  #####   ##   ###  ##
		0x3E, 0x87, 0x19, //  #####  ###    ##  ##
		0x1F, 0x03, 0x3B, // #####   ##      ## ###
		0x3F, 0x03, 0x3B, // ######  ##      ## ###
		0x1F, 0x03, 0x3B, // #####   ##      ## ###
		0x1F, 0xCF, 0x3B, // #####   ####  #### ###
		0x1F, 0xFE, 0x39, // #####    ########  ###
		0x3E, 0xFE, 0x19, //  #####   ########  ##
		0x1F, 0xFC, 0x38, // #####     ######   ###
		0x7E, 0x38, 0x1C, //  ######    ###    ###
		0x7C, 0x00, 0x0C, //   #####           ##
		0xFC, 0x00, 0x0E, //   ######         ###
		0xF8, 0xC3, 0x07, //    #######    #####
		0xF0, 0xFF, 0x03, //     ##############
		0xE0, 0xFF, 0x03, //      #############
		0x00, 0x1F, 0x00, //         #####
};


#define circle1_2_low_width 24
#define circle1_2_low_height 23
static U8 circle1_2_low_bits[] = { circle1_2_low_width , circle1_2_low_height,
		0x00, 0x7E, 0x00, //          ######
		0xC0, 0xFF, 0x03, //       ############
		0xF0, 0xFF, 0x07, //     ###############
		0xF8, 0x9F, 0x0F, //    ##########  #####
		0xF8, 0x01, 0x0C, //    ######         ##
		0xFC, 0x40, 0x18, //   ######      #    ##
		0x7C, 0xF9, 0x19, //   ##### #  ######  ##
		0x3F, 0xBC, 0x33, // ######    #### ###  ##
		0x3E, 0x06, 0x73, //  #####   ##     ##  ###
		0x3E, 0x06, 0x3E, //  #####   ##      #####
		0x1F, 0x0E, 0x36, // #####    ###     ## ##
		0x3E, 0x0E, 0x22, //  #####   ###     #   #
		0x1E, 0x0F, 0x77, //  ####   ####    ### ###
		0x1E, 0x7E, 0x33, //  ####    ###### ##  ##
		0x1E, 0xFE, 0x3B, //  ####    ######### ###
		0x3E, 0xFC, 0x3C, //  #####    ######  ####
		0x3C, 0x20, 0x0E, //   ####       #   ###
		0x78, 0x00, 0x0F, //    ####         ####
		0xF0, 0x43, 0x0B, //     ######    # ## #
		0xE0, 0xD7, 0x03, //      ###### # ####
		0x40, 0x7F, 0x01, //       # ####### #
		0x00, 0x5E, 0x00, //          #### #
		0x00, 0x04, 0x00, //           #
};


#define circle1_3_low_width 24
#define circle1_3_low_height 22
static U8 circle1_3_low_bits[] = { circle1_3_low_width , circle1_3_low_height,
		0x80, 0x3E, 0x00, //        # #####
		0xC0, 0xFF, 0x00, //       ##########
		0xF0, 0xFF, 0x01, //     #############
		0xF8, 0xFF, 0x07, //    ################
		0xFC, 0xFF, 0x0F, //   ##################
		0x7E, 0xD1, 0x0F, //  ###### #   # ######
		0x7E, 0x00, 0x1F, //  ######         #####
		0x1E, 0x00, 0x1E, //  ####            ####
		0x0F, 0x7C, 0x38, // ####      #####    ###
		0x0F, 0xFF, 0x38, // ####    ########   ###
		0x87, 0xC7, 0x39, // ###    ####   ###  ###
		0xC7, 0x07, 0x33, // ###   #####     ##  ##
		0xC7, 0x03, 0x33, // ###   ####      ##  ##
		0xC6, 0x03, 0x33, //  ##   ####      ##  ##
		0x8E, 0x87, 0x19, //  ###   ####    ##  ##
		0x8E, 0xC7, 0x19, //  ###   ####   ###  ##
		0x0E, 0xFF, 0x0D, //  ###    ######### ##
		0x1E, 0x3C, 0x0E, //  ####     ####   ###
		0x78, 0x00, 0x0F, //    ####         ####
		0xF0, 0xFF, 0x01, //     #############
		0xC0, 0xFF, 0x01, //       ###########
		0x80, 0x3E, 0x00, //        # #####
};


#define circle1_4_low_width 24
#define circle1_4_low_height 23
static U8 circle1_4_low_bits[] = { circle1_4_low_width , circle1_4_low_height,
		0x00, 0x90, 0x00, //             #  #
		0x80, 0xFF, 0x00, //        #########
		0xC0, 0xFF, 0x03, //       ############
		0xE0, 0xFF, 0x0F, //      ###############
		0xF0, 0xFF, 0x1F, //     #################
		0xF8, 0xE8, 0x1F, //    #####   # ########
		0x3C, 0x00, 0x3F, //   ####          ######
		0x18, 0x00, 0x3E, //    ##            #####
		0x1C, 0x04, 0x3D, //   ###     #     # ####
		0x1E, 0x7F, 0x78, //  ####   #######    ####
		0x8F, 0xFF, 0x78, // ####   #########   ####
		0x86, 0x9F, 0x79, //  ##    ######  ##  ####
		0x8E, 0x83, 0x79, //  ###   ###     ##  ####
		0xC4, 0x83, 0x71, //   #   ####     ##   ###
		0x9E, 0x03, 0x73, //  ####  ###      ##  ###
		0x88, 0x81, 0x39, //    #   ##      ##  ###
		0x3C, 0xC7, 0x39, //   ####  ###   ###  ###
		0x78, 0xFF, 0x38, //    #### ########   ###
		0xE0, 0x34, 0x1C, //      ###  # ##    ###
		0xF0, 0x21, 0x0F, //     #####    #  ####
		0x80, 0xF7, 0x03, //        #### ######
		0x80, 0xFF, 0x00, //        #########
		0x00, 0x44, 0x00, //           #   #
};


#define circle1_5_low_width 24
#define circle1_5_low_height 22
static U8 circle1_5_low_bits[] = { circle1_5_low_width , circle1_5_low_height,
		0x00, 0x3E, 0x00, //          #####
		0xF0, 0xFF, 0x01, //     #############
		0xF0, 0xFF, 0x03, //     ##############
		0xF8, 0xF0, 0x07, //    #####    #######
		0x1C, 0xC0, 0x0F, //   ###         ######
		0x0C, 0x80, 0x0F, //   ##           #####
		0x0E, 0x87, 0x1F, //  ###    ###    ######
		0xC7, 0x0F, 0x3E, // ###   ######     #####
		0xE6, 0x1F, 0x1F, //  ##  ########   #####
		0xE7, 0x1F, 0x3E, // ###  ########    #####
		0xF7, 0x3C, 0x3E, // ### ####  ####   #####
		0x37, 0x30, 0x3E, // ### ##      ##   #####
		0x37, 0x30, 0x3F, // ### ##      ##  ######
		0x37, 0x30, 0x3E, // ### ##      ##   #####
		0x66, 0x38, 0x1F, //  ##  ##    ###  #####
		0xE6, 0x18, 0x1F, //  ##  ###   ##   #####
		0xEE, 0x8F, 0x0F, //  ### #######   #####
		0x18, 0xC7, 0x07, //    ##   ###   #####
		0x38, 0xC0, 0x07, //    ###        #####
		0xF8, 0xF8, 0x03, //    #####   #######
		0xC0, 0xFF, 0x00, //       ##########
		0x00, 0x3F, 0x00, //         ######
};


#define circle1_6_low_width 24
#define circle1_6_low_height 23
static U8 circle1_6_low_bits[] = { circle1_6_low_width , circle1_6_low_height,
		0x00, 0x10, 0x00, //             #
		0x00, 0x3D, 0x00, //         # ####
		0x40, 0x7F, 0x01, //       # ####### #
		0xE0, 0xF5, 0x03, //      #### # ######
		0x68, 0xE1, 0x07, //    # ## #    ######
		0x78, 0x00, 0x0F, //    ####         ####
		0x38, 0x02, 0x1E, //    ###   #       ####
		0x9E, 0x1F, 0x3E, //  ####  ######    #####
		0xEE, 0x3F, 0x3C, //  ### #########    ####
		0x66, 0x3F, 0x3C, //  ##  ## ######    ####
		0x77, 0x78, 0x3C, // ### ###    ####   ####
		0x22, 0x38, 0x3E, //  #   #     ###   #####
		0x36, 0x38, 0x7C, //  ## ##     ###    #####
		0x3E, 0x30, 0x3E, //  #####      ##   #####
		0x67, 0x30, 0x3E, // ###  ##     ##   #####
		0xE6, 0x1E, 0x7E, //  ##  ### ####    ######
		0xCC, 0x4F, 0x1F, //   ##  ######  # #####
		0x0C, 0x81, 0x1F, //   ##    #      ######
		0x18, 0xC0, 0x0F, //    ##         ######
		0xF8, 0xFC, 0x0F, //    #####  ##########
		0xF0, 0xFF, 0x07, //     ###############
		0xE0, 0xFF, 0x01, //      ############
		0x00, 0x3F, 0x00, //         ######
};


#define circle1_7_low_width 24
#define circle1_7_low_height 22
static U8 circle1_7_low_bits[] = { circle1_7_low_width , circle1_7_low_height,
		0x00, 0x5F, 0x00, //         ##### #
		0xE0, 0xFF, 0x00, //      ###########
		0xE0, 0xFF, 0x03, //      #############
		0x3C, 0x80, 0x07, //   ####         ####
		0x1C, 0x0F, 0x1E, //   ###   ####     ####
		0xEC, 0x3F, 0x1C, //   ## #########    ###
		0xE6, 0x78, 0x1C, //  ##  ###   ####   ###
		0x66, 0x78, 0x1C, //  ##  ##    ####   ###
		0x33, 0xF0, 0x18, // ##  ##      ####   ##
		0x33, 0xF0, 0x38, // ##  ##      ####   ###
		0x33, 0xF8, 0x38, // ##  ##     #####   ###
		0xE7, 0x78, 0x38, // ###  ###   ####    ###
		0xC7, 0x3F, 0x3C, // ###   ########    ####
		0x87, 0x0F, 0x3C, // ###    #####      ####
		0x1E, 0x00, 0x1E, //  ####            ####
		0x3E, 0x80, 0x1F, //  #####         ######
		0xFC, 0xA2, 0x1F, //   ###### #   # ######
		0xFC, 0xFF, 0x0F, //   ##################
		0xF8, 0xFF, 0x07, //    ################
		0xE0, 0xFF, 0x03, //      #############
		0xC0, 0xFF, 0x00, //       ##########
		0x00, 0x5F, 0x00, //         ##### #
};


#define circle1_8_low_width 24
#define circle1_8_low_height 23
static U8 circle1_8_low_bits[] = { circle1_8_low_width , circle1_8_low_height,
		0x00, 0x11, 0x00, //         #   #
		0x80, 0xFF, 0x00, //        #########
		0xE0, 0xF7, 0x00, //      ###### ####
		0x78, 0xC2, 0x07, //    ####  #    #####
		0x1C, 0x96, 0x03, //   ###    ## #  ###
		0x8E, 0x7F, 0x0F, //  ###   ######## ####
		0xCE, 0x71, 0x1E, //  ###  ###   ###  ####
		0xCE, 0xC0, 0x08, //  ###  ##      ##   #
		0x67, 0xE0, 0x3C, // ###  ##      ###  ####
		0xC7, 0xE0, 0x11, // ###   ##     ####   #
		0xCF, 0xE0, 0x38, // ####  ##     ###   ###
		0xCF, 0xFC, 0x30, // ####  ##  ######    ##
		0x8F, 0xFF, 0x78, // ####   #########   ####
		0x0F, 0x7F, 0x3C, // ####    #######   ####
		0x5E, 0x10, 0x1C, //  #### #     #     ###
		0x3E, 0x00, 0x0C, //  #####            ##
		0x7E, 0x00, 0x1E, //  ######          ####
		0xFC, 0x8B, 0x0F, //   ######## #   #####
		0xFC, 0xFF, 0x07, //   #################
		0xF8, 0xFF, 0x03, //    ###############
		0xE0, 0xFF, 0x01, //      ############
		0x80, 0xFF, 0x00, //        #########
		0x80, 0x04, 0x00, //        #  #
};


/****************************************************************************
 * circle 2
 ****************************************************************************/


#define circle2_1_low_width 24
#define circle2_1_low_height 23
static U8 circle2_1_low_bits[] = { circle2_1_low_width , circle2_1_low_height,
		0x00, 0x3F, 0x00, //         ######
		0xC0, 0xFF, 0x01, //       ###########
		0xF0, 0xC0, 0x07, //     ####      #####
		0x30, 0x80, 0x0F, //     ##         #####
		0x1C, 0x1E, 0x0C, //   ###    ####     ##
		0x8C, 0xFF, 0x18, //   ##   #########   ##
		0xC2, 0xFF, 0x19, //  #    ###########  ##
		0xE6, 0xE7, 0x33, //  ##  ######  #####  ##
		0xE3, 0x81, 0x63, // ##   ####      ###   ##
		0xE3, 0x98, 0x63, // ##   ###   ##  ###   ##
		0xE3, 0xB8, 0x63, // ##   ###   ### ###   ##
		0xE3, 0xB8, 0x63, // ##   ###   ### ###   ##
		0xE3, 0x89, 0x63, // ##   ####  #   ###   ##
		0xE3, 0x80, 0x73, // ##   ###       ###  ###
		0xE2, 0x83, 0x33, //  #   #####     ###  ##
		0xC6, 0xFF, 0x39, //  ##   ###########  ###
		0x8E, 0xFF, 0x3C, //  ###   #########  ####
		0x0C, 0x7F, 0x1C, //   ##    #######   ###
		0x3C, 0x80, 0x1F, //   ####         ######
		0xF8, 0xE1, 0x07, //    ######    ######
		0xE0, 0xFF, 0x07, //      ##############
		0x80, 0xFF, 0x00, //        #########
		0x00, 0x1F, 0x00, //         #####
};



#define circle2_2_low_width 24
#define circle2_2_low_height 23
static U8 circle2_2_low_bits[] = { circle2_2_low_width , circle2_2_low_height,
		0x80, 0x76, 0x00, //        # ## ###
		0xA0, 0xFE, 0x03, //      # # #########
		0xF0, 0x40, 0x07, //     ####      # ###
		0x38, 0x00, 0x0E, //    ###           ###
		0x18, 0x5E, 0x1C, //    ##    #### #   ###
		0x0C, 0xFF, 0x18, //   ##    ########   ##
		0x04, 0xFF, 0x31, //   #     #########   ##
		0xC6, 0xEB, 0x33, //  ##   #### # #####  ##
		0xE6, 0x83, 0x73, //  ##  #####     ###  ###
		0xE7, 0xA1, 0x77, // ###  ####    # #### ###
		0xE3, 0x30, 0x67, // ##   ###    ##  ###  ##
		0xE3, 0x3C, 0x67, // ##   ###  ####  ###  ##
		0xE7, 0x90, 0x67, // ###  ###    #  ####  ##
		0xE6, 0xA1, 0x33, //  ##  ####    # ###  ##
		0xCE, 0xC3, 0x23, //  ###  ####    ####   #
		0xCC, 0xE7, 0x20, //   ##  #####  ###     #
		0x1E, 0xFF, 0x30, //  ####   ########    ##
		0x1C, 0x7E, 0x38, //   ###    ######    ###
		0xFC, 0x02, 0x1C, //   ###### #        ###
		0xF8, 0xE7, 0x0F, //    ########  #######
		0xC0, 0xFF, 0x05, //       ########### #
		0x80, 0xFE, 0x01, //        # ########
		0x00, 0x2C, 0x00, //           ## #
};



#define circle2_3_low_width 24
#define circle2_3_low_height 23
static U8 circle2_3_low_bits[] = { circle2_3_low_width , circle2_3_low_height,
		0x00, 0x7E, 0x00, //          ######
		0xC0, 0xFF, 0x01, //       ###########
		0xF0, 0x80, 0x06, //     ####       # ##
		0x78, 0x00, 0x06, //    ####          ##
		0x18, 0x00, 0x1C, //    ##             ###
		0x1C, 0xFF, 0x18, //   ###   ########   ##
		0x8C, 0xFF, 0x31, //   ##   ##########   ##
		0xCE, 0xFF, 0x33, //  ###  ############  ##
		0xEF, 0xC5, 0x63, // #### #### #   ####   ##
		0xE7, 0x81, 0x67, // ###  ####      ####  ##
		0xE7, 0x80, 0x67, // ###  ###       ####  ##
		0xE7, 0x3C, 0x67, // ###  ###  ####  ###  ##
		0xE7, 0x38, 0x67, // ###  ###   ###  ###  ##
		0xEE, 0x98, 0x63, //  ### ###   ##  ###   ##
		0xEE, 0x80, 0x33, //  ### ###       ###  ##
		0xDE, 0xFF, 0x3B, //  #### ############ ###
		0x9C, 0xFF, 0x39, //   ###  ##########  ###
		0x1C, 0xFF, 0x18, //   ###   ########   ##
		0x7C, 0x00, 0x1C, //   #####           ###
		0xF0, 0x00, 0x0F, //     ####        ####
		0xF0, 0x83, 0x03, //     ######     ###
		0xC0, 0xFF, 0x00, //       ##########
		0x00, 0x7E, 0x00, //          ######
};




#define circle2_4_low_width 24
#define circle2_4_low_height 23
static U8 circle2_4_low_bits[] = { circle2_4_low_width , circle2_4_low_height,
		0x00, 0x3C, 0x00, //           ####
		0x40, 0xFF, 0x00, //       # ########
		0xF0, 0xE7, 0x03, //     #######  #####
		0xF8, 0x01, 0x0E, //    ######        ###
		0x78, 0x00, 0x1C, //    ####           ###
		0x18, 0x7E, 0x38, //    ##    ######    ###
		0x9C, 0xFF, 0x10, //   ###  #########    #
		0x9E, 0xFF, 0x70, //  ####  #########    ###
		0xCC, 0xE3, 0x03, //   ##  ####   #####
		0xFE, 0xC1, 0x67, //  ########     #####  ##
		0xEF, 0x08, 0x67, // #### ###   #    ###  ##
		0x67, 0x88, 0x27, // ###  ##    #   ####  #
		0x66, 0x1C, 0x67, //  ##  ##   ###   ###  ##
		0xEF, 0xBA, 0x63, // #### ### # ### ###   ##
		0xEE, 0x81, 0x77, //  ### ####      #### ###
		0xCE, 0xE7, 0x23, //  ###  #####  #####   #
		0x0E, 0xFF, 0x31, //  ###    #########   ##
		0x08, 0xFF, 0x38, //    #    ########   ###
		0x1C, 0x3C, 0x1C, //   ###     ####    ###
		0x38, 0x00, 0x0E, //    ###           ###
		0x70, 0xE2, 0x07, //     ###  #   ######
		0xE0, 0xFF, 0x01, //      ############
		0x00, 0x7C, 0x00, //           #####
};




#define circle2_5_low_width 24
#define circle2_5_low_height 23
static U8 circle2_5_low_bits[] = { circle2_5_low_width , circle2_5_low_height,
		0x00, 0x7C, 0x00, //           #####
		0x80, 0xFF, 0x00, //        #########
		0xF0, 0xFF, 0x03, //     ##############
		0xF0, 0xC3, 0x0F, //     ######    ######
		0xFC, 0x00, 0x1E, //   ######         ####
		0x1C, 0x7F, 0x18, //   ###   #######    ##
		0x9E, 0xFF, 0x38, //  ####  #########   ###
		0xCE, 0xFF, 0x31, //  ###  ###########   ##
		0xE6, 0xE0, 0x23, //  ##  ###     #####   #
		0xE7, 0x80, 0x63, // ###  ###       ###   ##
		0xE3, 0xC8, 0x63, // ##   ###   #  ####   ##
		0xE3, 0x8E, 0x63, // ##   ### ###   ###   ##
		0xE3, 0x8E, 0x63, // ##   ### ###   ###   ##
		0xE3, 0x8C, 0x63, // ##   ###  ##   ###   ##
		0xE3, 0xC0, 0x63, // ##   ###      ####   ##
		0xE6, 0xF3, 0x33, //  ##  #####  ######  ##
		0xCC, 0xFF, 0x21, //   ##  ###########    #
		0x8C, 0xFF, 0x18, //   ##   #########   ##
		0x18, 0x3C, 0x1C, //    ##     ####    ###
		0xF8, 0x00, 0x06, //    #####         ##
		0xF0, 0x81, 0x07, //     #####      ####
		0xC0, 0xFF, 0x01, //       ###########
		0x00, 0x7E, 0x00, //          ######
};




#define circle2_6_low_width 24
#define circle2_6_low_height 23
static U8 circle2_6_low_bits[] = { circle2_6_low_width , circle2_6_low_height,
		0x00, 0x1A, 0x00, //          # ##
		0xC0, 0xBF, 0x00, //       ######## #
		0xD0, 0xFF, 0x01, //     # ###########
		0xF8, 0xF3, 0x0F, //    #######  ########
		0x1C, 0xA0, 0x1F, //   ###        # ######
		0x0E, 0x3F, 0x1C, //  ###    ######    ###
		0x86, 0x7F, 0x3C, //  ##    ########   ####
		0x82, 0xF3, 0x19, //  #     ###  #####  ##
		0xE2, 0xE1, 0x39, //  #   ####    ####  ###
		0xE6, 0xC2, 0x33, //  ##  ### #    ####  ##
		0xF3, 0x84, 0x73, // ##  ####  #    ###  ###
		0x73, 0x9E, 0x63, // ##  ###  ####  ###   ##
		0x73, 0x86, 0x63, // ##  ###  ##    ###   ##
		0xF7, 0xC2, 0x73, // ### #### #    ####  ###
		0xE7, 0xE0, 0x33, // ###  ###     #####  ##
		0xE6, 0xEB, 0x31, //  ##  ##### # ####   ##
		0xC6, 0x7F, 0x10, //  ##   #########     #
		0x8C, 0x7F, 0x18, //   ##   ########    ##
		0x1C, 0x3D, 0x0C, //   ###   # ####    ##
		0x38, 0x00, 0x0E, //    ###           ###
		0x70, 0x81, 0x07, //     ### #      ####
		0xE0, 0xBF, 0x02, //      ######### # #
		0x00, 0xB7, 0x00, //         ### ## #
};




#define circle2_7_low_width 24
#define circle2_7_low_height 23
static U8 circle2_7_low_bits[] = { circle2_7_low_width , circle2_7_low_height,
		0x00, 0x3F, 0x00, //         ######
		0x80, 0xFF, 0x01, //        ##########
		0xE0, 0xE0, 0x07, //      ###     ######
		0x78, 0x80, 0x07, //    ####        ####
		0x1C, 0x00, 0x1F, //   ###           #####
		0x8C, 0x7F, 0x1C, //   ##   ########   ###
		0xCE, 0xFF, 0x1C, //  ###  ##########  ###
		0xEE, 0xFF, 0x3D, //  ### ############ ####
		0xE6, 0x80, 0x3B, //  ##  ###       ### ###
		0xE3, 0x8C, 0x3B, // ##   ###  ##   ### ###
		0x73, 0x8E, 0x73, // ##  ###  ###   ###  ###
		0x73, 0x9E, 0x73, // ##  ###  ####  ###  ###
		0xF3, 0x80, 0x73, // ##  ####       ###  ###
		0xF3, 0xC0, 0x73, // ##  ####      ####  ###
		0xE3, 0xD1, 0x7B, // ##   ####   # #### ####
		0xE6, 0xFF, 0x39, //  ##  ############  ###
		0xC6, 0xFF, 0x18, //  ##   ##########   ##
		0x8C, 0x7F, 0x1C, //   ##   ########   ###
		0x1C, 0x00, 0x0C, //   ###             ##
		0x30, 0x00, 0x0F, //     ##          ####
		0xB0, 0x80, 0x07, //     ## #       ####
		0xC0, 0xFF, 0x01, //       ###########
		0x00, 0x3F, 0x00, //         ######
};




#define circle2_8_low_width 24
#define circle2_8_low_height 23
static U8 circle2_8_low_bits[] = { circle2_8_low_width , circle2_8_low_height,
		0x00, 0x1F, 0x00, //         #####
		0xC0, 0xFF, 0x03, //       ############
		0xF0, 0x23, 0x07, //     ######   #  ###
		0x38, 0x00, 0x0E, //    ###           ###
		0x1C, 0x1E, 0x1C, //   ###    ####     ###
		0x8E, 0x7F, 0x08, //  ###   ########    #
		0xC6, 0x7F, 0x38, //  ##   #########    ###
		0xE2, 0xF3, 0x39, //  #   #####  #####  ###
		0xF7, 0xC0, 0x3B, // ### ####      #### ###
		0xE3, 0xAE, 0x7B, // ##   ### ### # ### ####
		0x73, 0x1C, 0x33, // ##  ###   ###   ##  ##
		0xF2, 0x08, 0x73, //  #  ####   #    ##  ###
		0x73, 0x88, 0x7B, // ##  ###    #   ### ####
		0xF3, 0xC1, 0x3F, // ##  #####     ########
		0xE0, 0xE3, 0x19, //      #####   ####  ##
		0x87, 0xFF, 0x3C, // ###    #########  ####
		0x84, 0xFF, 0x1C, //   #    #########  ###
		0x0E, 0x3F, 0x0C, //  ###    ######    ##
		0x1C, 0x00, 0x0F, //   ###           ####
		0x38, 0xC0, 0x0F, //    ###        ######
		0xE0, 0xF3, 0x07, //      #####  #######
		0x80, 0x7F, 0x01, //        ######## #
		0x00, 0x1E, 0x00, //          ####
};


/****************************************************************************
 * explosion 1
 ****************************************************************************/
#define explos1_1_low_width 24
#define explos1_1_low_height 7
static U8 explos1_1_low_bits[] = { explos1_1_low_width , explos1_1_low_height,
		0x00, 0x08, 0x00, //            #
		0x00, 0x36, 0x00, //          ## ##
		0x00, 0x7E, 0x00, //          ######
		0x00, 0x7E, 0x00, //          ######
		0x00, 0x7C, 0x00, //           #####
		0x00, 0x5C, 0x00, //           ### #
		0x00, 0x20, 0x00, //              #
};



#define explos1_2_low_width 24
#define explos1_2_low_height 11
static U8 explos1_2_low_bits[] = { explos1_2_low_width , explos1_2_low_height,
		0x00, 0xA0, 0x01, //              # ##
		0x00, 0xFE, 0x01, //          ########
		0x00, 0xFE, 0x03, //          #########
		0x00, 0xFF, 0x03, //         ##########
		0x80, 0xFF, 0x07, //        ############
		0x00, 0xFE, 0x07, //          ##########
		0x00, 0xFF, 0x03, //         ##########
		0x00, 0xFF, 0x03, //         ##########
		0x00, 0xFE, 0x03, //          #########
		0x00, 0xFA, 0x05, //          # ###### #
		0x00, 0xF4, 0x01, //           # #####
};



#define explos1_3_low_width 24
#define explos1_3_low_height 13
static U8 explos1_3_low_bits[] = { explos1_3_low_width , explos1_3_low_height,
		0x00, 0x68, 0x00, //            # ##
		0x80, 0xFF, 0x00, //        #########
		0x80, 0xFF, 0x00, //        #########
		0xE0, 0xFF, 0x00, //      ###########
		0xC0, 0xFF, 0x01, //       ###########
		0xE0, 0xFF, 0x01, //      ############
		0xC0, 0xFF, 0x01, //       ###########
		0xE0, 0xFF, 0x03, //      #############
		0xE0, 0xFE, 0x01, //      ### ########
		0xC0, 0xBF, 0x00, //       ######## #
		0xC0, 0xEF, 0x01, //       ###### ####
		0x80, 0xFE, 0x00, //        # #######
		0x00, 0x64, 0x00, //           #  ##
};



#define explos1_4_low_width 24
#define explos1_4_low_height 14
static U8 explos1_4_low_bits[] = { explos1_4_low_width , explos1_4_low_height,
		0x00, 0x10, 0x00, //             #
		0x00, 0x70, 0x01, //             ### #
		0x80, 0xF7, 0x03, //        #### ######
		0xC0, 0xFB, 0x05, //       #### ###### #
		0x80, 0xFE, 0x03, //        # #########
		0xA0, 0xFF, 0x07, //      # ############
		0xC0, 0xFE, 0x03, //       ## #########
		0x60, 0xBF, 0x06, //      ## ###### # ##
		0xA0, 0xFF, 0x05, //      # ########## #
		0xD0, 0x7E, 0x07, //     # ## ###### ###
		0xE0, 0xF6, 0x00, //      ### ## ####
		0xA0, 0xFD, 0x03, //      # ## ########
		0xC0, 0xAD, 0x00, //       ### ## # #
		0x00, 0x0A, 0x00, //          # #
};




#define explos1_5_low_width 24
#define explos1_5_low_height 13
static U8 explos1_5_low_bits[] = { explos1_5_low_width , explos1_5_low_height,
		0x00, 0x90, 0x00, //             #  #
		0x00, 0x24, 0x01, //           #  #  #
		0x00, 0x59, 0x02, //         #  ## #  #
		0x80, 0xB4, 0x05, //        #  # ## ## #
		0x00, 0x7D, 0x01, //         # ##### #
		0xA0, 0x6A, 0x0B, //      # # # # ## ## #
		0xC0, 0xDB, 0x02, //       #### ## ## #
		0x00, 0x76, 0x01, //          ## ### #
		0x10, 0x54, 0x03, //     #     # # # ##
		0xA0, 0x54, 0x05, //      # #  # # # # #
		0x00, 0xA9, 0x02, //         #  # # # #
		0x40, 0x12, 0x00, //       #  #  #
		0x40, 0x04, 0x00, //       #   #

};




#define explos1_6_low_width 24
#define explos1_6_low_height 10
static U8 explos1_6_low_bits[] = { explos1_6_low_width , explos1_6_low_height,
		0x00, 0x54, 0x00, //           # # #
		0x00, 0x08, 0x00, //            #
		0x40, 0x50, 0x00, //       #     # #
		0x40, 0x92, 0x00, //       #  #  #  #
		0x80, 0x24, 0x02, //        #  #  #   #
		0x00, 0x91, 0x00, //         #   #  #
		0x00, 0x22, 0x00, //          #   #
		0x00, 0x80, 0x00, //                #
		0x00, 0x24, 0x00, //           #  #
		0x00, 0x00, 0x01, //                 #
};




#define explos1_7_low_width 24
#define explos1_7_low_height 3
static U8 explos1_7_low_bits[] = { explos1_7_low_width , explos1_7_low_height,
		0x00, 0x05, 0x00, //         # #
		0x00, 0x08, 0x00, //            #
		0x00, 0x02, 0x00, //          #
};




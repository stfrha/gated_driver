//////////////////////////////////////////////////////////////////////////
// This file contains a HD44780 font and a font for big numbers.        //
// The HD44780 font in this file was shamelessly stolen from            //
// Michael Reinelt / lcd4linux and is                                   //
//  Copyright 1999, 2000 by Michael Reinelt (reinelt@eunet.at)          //
// The rest of this file is                                             //
//                                                                      //
// (C) 2001 Robin Adams ( robin@adams-online.de )                       //
//                                                                      //
// This file is released under the GPL. See file COPYING in this        //
// package for further details.                                         //
//////////////////////////////////////////////////////////////////////////

#define b______ 0x00
#define b_____O 0x01
#define b____O_ 0x02
#define b____OO 0x03
#define b___O__ 0x04
#define b___O_O 0x05
#define b___OO_ 0x06
#define b___OOO 0x07
#define b__O___ 0x08
#define b__O__O 0x09
#define b__O_O_ 0x0a
#define b__O_OO 0x0b
#define b__OO__ 0x0c
#define b__OO_O 0x0d
#define b__OOO_ 0x0e
#define b__OOOO 0x0f
#define b_O____ 0x10
#define b_O___O 0x11
#define b_O__O_ 0x12
#define b_O__OO 0x13
#define b_O_O__ 0x14
#define b_O_O_O 0x15
#define b_O_OO_ 0x16
#define b_O_OOO 0x17
#define b_OO___ 0x18
#define b_OO__O 0x19
#define b_OO_O_ 0x1a
#define b_OO_OO 0x1b
#define b_OOO__ 0x1c
#define b_OOO_O 0x1d
#define b_OOOO_ 0x1e
#define b_OOOOO 0x1f
#define b_OOOOO 0x1f
#define bOOOOOO 0x3f

unsigned char fontmap[256][8] = {
    [0x20] {b______,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______},
    [0x21] {b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b______,
	    b______,
	    b___O__,
	    b______},
    [0x22] {b__O_O_,
	    b__O_O_,
	    b__O_O_,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______},
    [0x23] {b__O_O_,
	    b__O_O_,
	    b_OOOOO,
	    b__O_O_,
	    b_OOOOO,
	    b__O_O_,
	    b__O_O_,
	    b______},
    [0x24] {b___O__,
	    b__OOOO,
	    b_O_O__,
	    b__OOO_,
	    b___O_O,
	    b_OOOO_,
	    b___O__,
	    b______},
    [0x25] {b_OO___,
	    b_OO__O,
	    b____O_,
	    b___O__,
	    b__O___,
	    b_O__OO,
	    b____OO,
	    b______},
    [0x26] {b__OO__,
	    b_O__O_,
	    b_O_O__,
	    b__O___,
	    b_O_O_O,
	    b_O__O_,
	    b__OO_O,
	    b______},
    [0x27] {b__OO__,
	    b___O__,
	    b__O___,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______},
    [0x28] {b____O_,
	    b___O__,
	    b__O___,
	    b__O___,
	    b__O___,
	    b___O__,
	    b____O_,
	    b______},
    [0x29] {b__O___,
	    b___O__,
	    b____O_,
	    b____O_,
	    b____O_,
	    b___O__,
	    b__O___,
	    b______},
    [0x2a] {b______,
	    b___O__,
	    b_O_O_O,
	    b__OOO_,
	    b_O_O_O,
	    b___O__,
	    b______,
	    b______},
    [0x2b] {b______,
	    b___O__,
	    b___O__,
	    b_OOOOO,
	    b___O__,
	    b___O__,
	    b______,
	    b______},
    [0x2c] {b______,
	    b______,
	    b______,
	    b______,
	    b__OO__,
	    b___O__,
	    b__O___,
	    b______},
    [0x2d] {b______,
	    b______,
	    b______,
	    b_OOOOO,
	    b______,
	    b______,
	    b______,
	    b______},
    [0x2e] {b______,
	    b______,
	    b______,
	    b______,
	    b______,
	    b__OO__,
	    b__OO__,
	    b______},
    [0x2f] {b______,
	    b_____O,
	    b____O_,
	    b___O__,
	    b__O___,
	    b_O____,
	    b______,
	    b______},
    [0x30] {b__OOO_,
	    b_O___O,
	    b_O__OO,
	    b_O_O_O,
	    b_OO__O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x31] {b___O__,
	    b__OO__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b__OOO_,
	    b______},
    [0x32] {b__OOO_,
	    b_O___O,
	    b_____O,
	    b____O_,
	    b___O__,
	    b__O___,
	    b_OOOOO,
	    b______},
    [0x33] {b_OOOOO,
	    b____O_,
	    b___O__,
	    b____O_,
	    b_____O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x34] {b____O_,
	    b___OO_,
	    b__O_O_,
	    b_O__O_,
	    b_OOOOO,
	    b____O_,
	    b____O_,
	    b______},
    [0x35] {b_OOOOO,
	    b_O____,
	    b_O____,
	    b_OOOO_,
	    b_____O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x36] {b___OO_,
	    b__O___,
	    b_O____,
	    b_OOOO_,
	    b_O___O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x37] {b_OOOOO,
	    b_____O,
	    b____O_,
	    b___O__,
	    b__O___,
	    b__O___,
	    b__O___,
	    b______},
    [0x38] {b__OOO_,
	    b_O___O,
	    b_O___O,
	    b__OOO_,
	    b_O___O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x39] {b__OOO_,
	    b_O___O,
	    b_O___O,
	    b__OOOO,
	    b_____O,
	    b____O_,
	    b__OO__,
	    b______},
    [0x3a] {b______,
	    b__OO__,
	    b__OO__,
	    b______,
	    b__OO__,
	    b__OO__,
	    b______,
	    b______},
    [0x3b] {b______,
	    b__OO__,
	    b__OO__,
	    b______,
	    b__OO__,
	    b___O__,
	    b__O___,
	    b______},
    [0x3c] {b____O_,
	    b___O__,
	    b__O___,
	    b_O____,
	    b__O___,
	    b___O__,
	    b____O_,
	    b______},
    [0x3d] {b______,
	    b______,
	    b_OOOOO,
	    b______,
	    b_OOOOO,
	    b______,
	    b______,
	    b______},
    [0x3e] {b_O____,
	    b__O___,
	    b___O__,
	    b____O_,
	    b___O__,
	    b__O___,
	    b_O____,
	    b______},
    [0x3f] {b__OOO_,
	    b_O___O,
	    b_____O,
	    b____O_,
	    b___O__,
	    b______,
	    b___O__,
	    b______},
    [0x40] {b__OOO_,
	    b_O___O,
	    b_____O,
	    b__OO_O,
	    b_O_O_O,
	    b_O_O_O,
	    b__OOO_,
	    b______},
    [0x41] {b__OOO_,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_OOOOO,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x42] {b_OOOO_,
	    b_O___O,
	    b_O___O,
	    b_OOOO_,
	    b_O___O,
	    b_O___O,
	    b_OOOO_,
	    b______},
    [0x43] {b__OOO_,
	    b_O___O,
	    b_O____,
	    b_O____,
	    b_O____,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x44] {b_OOO__,
	    b_O__O_,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O__O_,
	    b_OOO__,
	    b______},
    [0x45] {b_OOOOO,
	    b_O____,
	    b_O____,
	    b_OOOO_,
	    b_O____,
	    b_O____,
	    b_OOOOO,
	    b______},
    [0x46] {b_OOOOO,
	    b_O____,
	    b_O____,
	    b_OOOO_,
	    b_O____,
	    b_O____,
	    b_O____,
	    b______},
    [0x47] {b__OOO_,
	    b_O___O,
	    b_O____,
	    b_O_OOO,
	    b_O___O,
	    b_O___O,
	    b__OOOO,
	    b______},
    [0x48] {b_O___O,
	    b_O___O,
	    b_O___O,
	    b_OOOOO,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x49] {b__OOO_,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b__OOO_,
	    b______},
    [0x4a] {b___OOO,
	    b____O_,
	    b____O_,
	    b____O_,
	    b____O_,
	    b_O__O_,
	    b__OO__,
	    b______},
    [0x4b] {b_O___O,
	    b_O__O_,
	    b_O_O__,
	    b_OO___,
	    b_O_O__,
	    b_O__O_,
	    b_O___O,
	    b______},
    [0x4c] {b_O____,
	    b_O____,
	    b_O____,
	    b_O____,
	    b_O____,
	    b_O____,
	    b_OOOOO,
	    b______},
    [0x4d] {b_O___O,
	    b_OO_OO,
	    b_O_O_O,
	    b_O_O_O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x4e] {b_O___O,
	    b_O___O,
	    b_OO__O,
	    b_O_O_O,
	    b_O__OO,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x4f] {b__OOO_,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x50] {b_OOOO_,
	    b_O___O,
	    b_O___O,
	    b_OOOO_,
	    b_O____,
	    b_O____,
	    b_O____,
	    b______},
    [0x51] {b__OOO_,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O_O_O,
	    b_O__O_,
	    b__OO_O,
	    b______},
    [0x52] {b_OOOO_,
	    b_O___O,
	    b_O___O,
	    b_OOOO_,
	    b_O_O__,
	    b_O__O_,
	    b_O___O,
	    b______},
    [0x53] {b__OOOO,
	    b_O____,
	    b_O____,
	    b__OOO_,
	    b_____O,
	    b_____O,
	    b_OOOO_,
	    b______},
    [0x54] {b_OOOOO,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b______},
    [0x55] {b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x56] {b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b__O_O_,
	    b___O__,
	    b______},
    [0x57] {b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O_O_O,
	    b_O_O_O,
	    b_O_O_O,
	    b__O_O_,
	    b______},
    [0x58] {b_O___O,
	    b_O___O,
	    b__O_O_,
	    b___O__,
	    b__O_O_,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x59] {b_O___O,
	    b_O___O,
	    b_O___O,
	    b__O_O_,
	    b___O__,
	    b___O__,
	    b___O__,
	    b______},
    [0x5a] {b_OOOOO,
	    b_____O,
	    b____O_,
	    b___O__,
	    b__O___,
	    b_O____,
	    b_OOOOO,
	    b______},
    [0x5b] {b__OOO_,
	    b__O___,
	    b__O___,
	    b__O___,
	    b__O___,
	    b__O___,
	    b__OOO_,
	    b______},
    [0x5c] {b_O___O,
	    b__O_O_,
	    b_OOOOO,
	    b___O__,
	    b_OOOOO,
	    b___O__,
	    b___O__,
	    b______},
    [0x5d] {b__OOO_,
	    b____O_,
	    b____O_,
	    b____O_,
	    b____O_,
	    b____O_,
	    b__OOO_,
	    b______},
    [0x5e] {b___O__,
	    b__O_O_,
	    b_O___O,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______},
    [0x5f] {b______,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______,
	    b_OOOOO,
	    b______},
    [0x60] {b__O___,
	    b___O__,
	    b____O_,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______},
    [0x61] {b______,
	    b______,
	    b__OOO_,
	    b_____O,
	    b__OOOO,
	    b_O___O,
	    b__OOOO,
	    b______},
    [0x62] {b_O____,
	    b_O____,
	    b_O____,
	    b_O_OO_,
	    b_OO__O,
	    b_O___O,
	    b_OOOO_,
	    b______},
    [0x63] {b______,
	    b______,
	    b__OOO_,
	    b_O____,
	    b_O____,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x64] {b_____O,
	    b_____O,
	    b_____O,
	    b__OO_O,
	    b_O__OO,
	    b_O___O,
	    b__OOOO,
	    b______},
    [0x65] {b______,
	    b______,
	    b__OOO_,
	    b_O___O,
	    b_OOOOO,
	    b_O____,
	    b__OOO_,
	    b______},
    [0x66] {b___OO_,
	    b__O__O,
	    b__O___,
	    b_OOO__,
	    b__O___,
	    b__O___,
	    b__O___,
	    b______},
    [0x67] {b______,
	    b__OOOO,
	    b_O___O,
	    b_O___O,
	    b__OOOO,
	    b_____O,
	    b__OOO_,
	    b______},
    [0x68] {b_O____,
	    b_O____,
	    b_O_OO_,
	    b_OO__O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x69] {b___O__,
	    b______,
	    b__OO__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b__OOO_,
	    b______},
    [0x6a] {b____O_,
	    b______,
	    b___OO_,
	    b____O_,
	    b____O_,
	    b_O__O_,
	    b__OO__,
	    b______},
    [0x6b] {b__O___,
	    b__O___,
	    b__O__O,
	    b__O_O_,
	    b__OO__,
	    b__O_O_,
	    b__O__O,
	    b______},
    [0x6c] {b__OO__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b__OOO_,
	    b______},
    [0x6d] {b______,
	    b______,
	    b_OO_O_,
	    b_O_O_O,
	    b_O_O_O,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x6e] {b______,
	    b______,
	    b_OOOO_,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b______},
    [0x6f] {b______,
	    b______,
	    b__OOO_,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b__OOO_,
	    b______},
    [0x70] {b______,
	    b______,
	    b_OOOO_,
	    b_O___O,
	    b_OOOO_,
	    b_O____,
	    b_O____,
	    b______},
    [0x71] {b______,
	    b______,
	    b__OO_O,
	    b_O__OO,
	    b__OOOO,
	    b_____O,
	    b_____O,
	    b______},
    [0x72] {b______,
	    b______,
	    b_O_OO_,
	    b_OO__O,
	    b_O____,
	    b_O____,
	    b_O____,
	    b______},
    [0x73] {b______,
	    b______,
	    b__OOO_,
	    b_O____,
	    b__OOO_,
	    b_____O,
	    b_OOOO_,
	    b______},
    [0x74] {b__O___,
	    b_OOO__,
	    b__O___,
	    b__O___,
	    b__O___,
	    b__O__O,
	    b___OO_,
	    b______},
    [0x75] {b______,
	    b______,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O__OO,
	    b__OO_O,
	    b______},
    [0x76] {b______,
	    b______,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b__O_O_,
	    b___O__,
	    b______},
    [0x77] {b______,
	    b______,
	    b_O___O,
	    b_O___O,
	    b_O___O,
	    b_O_O_O,
	    b__O_O_,
	    b______},
    [0x78] {b______,
	    b______,
	    b_O___O,
	    b__O_O_,
	    b___O__,
	    b__O_O_,
	    b_O___O,
	    b______},
    [0x79] {b______,
	    b______,
	    b_O___O,
	    b_O___O,
	    b__OOOO,
	    b_____O,
	    b__OOO_,
	    b______},
    [0x7a] {b______,
	    b______,
	    b_OOOOO,
	    b____O_,
	    b___O__,
	    b__O___,
	    b_OOOOO,
	    b______},
    [0x7b] {b____O_,
	    b___O__,
	    b___O__,
	    b__O___,
	    b___O__,
	    b___O__,
	    b____O_,
	    b______},
    [0x7c] {b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b___O__,
	    b______},
    [0x7d] {b__O___,
	    b___O__,
	    b___O__,
	    b____O_,
	    b___O__,
	    b___O__,
	    b__O___,
	    b______},
    [0x7e] {b______,
	    b___O__,
	    b____O_,
	    b_OOOOO,
	    b____O_,
	    b___O__,
	    b______,
	    b______},

    [0x7f] {b______,
	    b___O__,
	    b__O___,
	    b_OOOOO,
	    b__O___,
	    b___O__,
	    b______,
	    b______},
    [0xb0] {b__OOO_,
	    b__O_O_,
	    b__OOO_,
	    b______,
	    b______,
	    b______,
	    b______,
	    b______},
    [0xff] {bOOOOOO,
	    bOOOOOO,
	    bOOOOOO,
	    bOOOOOO,
	    bOOOOOO,
	    bOOOOOO,
	    bOOOOOO,
	    bOOOOOO},
};

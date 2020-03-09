#pragma once
#include "twogd/twogd.h"

#define S_STYLE_BOXING 50

#define S_STYLE_HOR_BOXES 20
#define S_STYLE_VER_BOXES 15

#define S_STYLE_WIDTH (S_STYLE_BOXING * S_STYLE_HOR_BOXES)
#define S_STYLE_HEIGHT (S_STYLE_BOXING * S_STYLE_VER_BOXES)

#define S_BITSTREAM_LENGTH 32
#define S_BITSTREAM_STREAMS 5

static GDCOLOR c_finish(255,0,255);
static GDCOLOR c_sellected(255,255,255);


typedef class c_bitstream {
public:
	char __stdcall init(int i_bits);
	void __stdcall deinit();
	char* c_pBits;
} SBITSTREAM;


typedef class c_streamlist {
private: 


	char i_streams, i_bits;
	GDCODEC* gd_pCodec;
	SBITSTREAM* s_pStreams;

	char i_cursor_stream{0};
	char i_cursor_bit{0};

	
public:
	void __stdcall init(GDCODEC*,char,char);
	void __stdcall deinit();
	void __stdcall inputhandler();
	void __stdcall render();

}SSTREAMLIST ;
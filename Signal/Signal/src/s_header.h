#pragma once
#include "twogd.h"


#define S_STYLE_WIDTH 500
#define S_STYLE_HEIGHT 400
#define S_STYLE_BOXING 50

#define S_BITSTREAM_LENGTH 32
#define S_BITSTREAM_STREAMS 5

static const GDCOLOR c_finish(255,255,255);
static const GDCOLOR c_sellected(255,255,255);


typedef class c_bitstream {
public:
	char __stdcall init(int i_bits);
	void __stdcall deinit();
	char* c_pBits;
} SBITSTREAM;


typedef class c_streamlist {
private: 
	char i_streams, i_bits;
	SBITSTREAM* s_pStreams;

	char i_cursor_stream{0};
	char i_cursor_bit{0};

	
public:
	void __stdcall init(int i_bits, int i_streams);
	void __stdcall deinit();
	void __stdcall inputhandler();
	void __stdcall render(GDCODEC* o_pRender);

}SSTREAMLIST ;
#include"s_header.h"

#include <chrono>

GDCONSOLE gd_Console;
GDCODEC gd_Display;

SSTREAMLIST sl_System;

unsigned char __WAY gdmain() {
	win::i_Width = 300;
	win::i_Height = 200;
	gd_Console.Create();

	gd_Display.Prepare(win::i_Width, win::i_Height);
	sl_System.init(S_BITSTREAM_LENGTH, S_BITSTREAM_STREAMS);

	return TRUE;
}
unsigned char __WAY gdupdate() {

	gd_Display.CleanBuffer();
	sl_System.render(&gd_Display);
	SetScreenBuffer(gd_Display.d_pOutputStream, win::i_Width, win::i_Height);

	return TRUE;

}
void __WAY gdclose() {
	gd_Display.Dispose();
}
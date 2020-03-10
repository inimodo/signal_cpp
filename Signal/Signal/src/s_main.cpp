#include"s_header.h"

#include <chrono>
#include <thread>
GDCONSOLE gd_Console;
GDCODEC gd_Display;

SSTREAMLIST sl_System;

void __WAY inputroutine();
std::thread t_Inputroutine(inputroutine);

unsigned char __WAY gdmain() {
	win::i_Width = S_STYLE_WIDTH;
	win::i_Height = S_STYLE_HEIGHT;
	gd_Console.Create();

	sl_System.init(&gd_Display, S_BITSTREAM_STREAMS,S_BITSTREAM_LENGTH);

	gd_Display.Prepare(win::i_Width, win::i_Height);

	return TRUE;
}
unsigned char __WAY gdupdate() {

	gd_Display.CleanBuffer();
	sl_System.render_background();
	sl_System.render();
	SetScreenBuffer(gd_Display.d_pOutputStream, win::i_Width, win::i_Height);

	return TRUE;

}
void __WAY gdclose() {
	gd_Display.Dispose();
}
void __WAY inputroutine() 
{
	while (1)
	{
		sl_System.inputhandler();
	}
}
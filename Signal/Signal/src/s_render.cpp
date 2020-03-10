#include "s_header.h"

char __stdcall
c_bitstream::init(int i_bits)
{
	this->c_pBits = (char*)malloc(i_bits);
	if (this->c_pBits == NULL) return FALSE;
	else return TRUE;
}

void __stdcall 
c_bitstream::deinit() 
{
	if (this->c_pBits != NULL) free(this->c_pBits);
}

void __stdcall 
c_streamlist::init(GDCODEC * gd_pCodec,char i_streams,char i_bits)
{
	this->s_pStreams = (SBITSTREAM*)malloc(sizeof(SBITSTREAM)* i_streams);
	for (int i_index = 0; i_index < i_streams; i_index++)
	{
		if (this->s_pStreams[i_index].init(i_bits) == FALSE)
		{
			for (int i_subindex = 0; i_subindex <= i_index; i_subindex++)
			{
				this->s_pStreams[i_index].deinit();
			}
			free(this->s_pStreams);
		}
		else 
		{
			for (int i_subindex = 0; i_subindex < i_bits; i_subindex++)
			{
				this->s_pStreams[i_index].c_pBits[i_subindex] = i_subindex %2;
			}
		}
	}
	this->gd_pCodec = gd_pCodec;
	this->i_bits = i_bits;
	this->i_streams = i_streams;
}	

void __stdcall 
c_streamlist::deinit() 
{
	for (int i_subindex = 0; i_subindex < this->i_streams; i_subindex++)
	{
		this->s_pStreams[i_subindex].deinit();
	}
	free(this->s_pStreams);
}
void __stdcall
c_streamlist::render_background()
{

	int i_offset;
	GDPOINT p_One;
	for (int i_streamindex = 0; i_streamindex < S_STYLE_VER_BOXES; i_streamindex++)
	{
		if (i_streamindex == this->i_streams)break;

		i_offset = i_streamindex * S_STYLE_BOXING * 2 + S_STYLE_BOXING;

		p_One.f_Pos[0] = 0;
		p_One.f_Pos[1] = i_offset + S_STYLE_BOXING;

		this->gd_pCodec->DrawHLine(&p_One, S_STYLE_BOXING * S_STYLE_HOR_BOXES, &c_support);
	}

	for (int i_bitindex = 0; i_bitindex < S_STYLE_HOR_BOXES; i_bitindex++)
	{
		p_One.f_Pos[0] = S_STYLE_BOXING* i_bitindex;
		p_One.f_Pos[1] = 0;
		this->gd_pCodec->DrawVLine(&p_One, S_STYLE_BOXING * S_STYLE_VER_BOXES, &c_support);
	}
}
void __stdcall 
c_streamlist::render() 
{
	int i_offset;
	GDPOINT p_One, p_Two;
	for (int i_streamindex = 0; i_streamindex < S_STYLE_VER_BOXES; i_streamindex++)
	{
		i_offset = i_streamindex * S_STYLE_BOXING * 2 + S_STYLE_BOXING;

		if (i_streamindex == this->i_streams)break;
		for (int i_bitindex = 0; i_bitindex < S_STYLE_HOR_BOXES; i_bitindex++)
		{
			if (i_bitindex == this->i_bits)break;

			p_One.f_Pos[0] = i_bitindex * S_STYLE_BOXING;
			p_Two.f_Pos[0] = (i_bitindex+1) * S_STYLE_BOXING;
			
			p_One.f_Pos[1] = i_offset + (S_STYLE_BOXING * s_pStreams[i_streamindex].c_pBits[i_bitindex]);
			p_Two.f_Pos[1] = i_offset;
			
			if(i_bitindex == this->i_cursor_bit && i_streamindex == this->i_cursor_stream)
				this->gd_pCodec->DrawHLine(&p_One, S_STYLE_BOXING, &c_sellected);
			else	
				this->gd_pCodec->DrawHLine(&p_One, S_STYLE_BOXING, &c_finish);
			if(s_pStreams[i_streamindex].c_pBits[i_bitindex+1] != s_pStreams[i_streamindex].c_pBits[i_bitindex])
				this->gd_pCodec->DrawVLine(&p_Two, S_STYLE_BOXING, &c_finish);
		}
	}
}
void __stdcall
c_streamlist::inputhandler() 
{
	if (GetAsyncKeyState(VK_DOWN)!=0)
	{
		this->i_cursor_stream++;
		if (this->i_cursor_stream == this->i_streams)
			this->i_cursor_stream = 0;
		while (GetAsyncKeyState(VK_DOWN) != 0)
		{}
	}
	if (GetAsyncKeyState(VK_UP) != 0)
	{
		this->i_cursor_stream--;
		if (this->i_cursor_stream == -1)
			this->i_cursor_stream = this->i_streams-1;
		while (GetAsyncKeyState(VK_UP) != 0)
		{}
	}
	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		this->i_cursor_bit++;
		if (this->i_cursor_bit == this->i_bits)
			this->i_cursor_bit = 0;
		while (GetAsyncKeyState(VK_RIGHT) != 0)
		{}
	}
	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		this->i_cursor_bit--;
		if (this->i_cursor_bit == -1)
			this->i_cursor_bit = this->i_bits-1;
		while (GetAsyncKeyState(VK_LEFT) != 0)
		{}
	}
	if (GetAsyncKeyState(VK_CONTROL) != 0)
	{
		if (s_pStreams[this->i_cursor_stream].c_pBits[this->i_cursor_bit] == 0)
			s_pStreams[this->i_cursor_stream].c_pBits[this->i_cursor_bit] = 1;
		else
			s_pStreams[this->i_cursor_stream].c_pBits[this->i_cursor_bit] = 0;
		while (GetAsyncKeyState(VK_CONTROL) != 0)
		{}
	}
}
void __stdcall
c_streamlist::savefile(char* c_pPath) 
{

}

void __stdcall 
c_streamlist::loadfile(char* c_pPath) 
{

}
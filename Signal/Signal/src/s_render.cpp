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
c_streamlist::init(int i_bits, int i_streams)
{
	this->s_pStreams = (SBITSTREAM*)malloc(sizeof(SBITSTREAM)*i_streams);
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
				this->s_pStreams->c_pBits[i_subindex] = i_bits%2;
			}
		}
	}
	this->i_streams = i_streams;
	this->i_bits = i_bits;
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
c_streamlist::render(GDCODEC* o_pRender) 
{

	int i_offset;
	GDPOINT p_One, p_Two,p_Last;
	GDCOLOR c_Color(255,255,0);
	for (int i_streamindex = 0; i_streamindex < this->i_streams; i_streamindex++)
	{
		for (int i_bitindex = 0; i_bitindex < this->i_bits; i_bitindex++)
		{
			i_offset = i_streamindex * S_STYLE_BOXING*2;
			p_One.f_Pos[0] = i_bitindex * S_STYLE_BOXING;
			p_Two.f_Pos[0] = (i_bitindex+1) * S_STYLE_BOXING;
				
			p_One.f_Pos[1] = i_offset + S_STYLE_BOXING ;
			p_Two.f_Pos[1] = i_offset + S_STYLE_BOXING ;
			//p_One.f_Pos[1] = i_offset + S_STYLE_BOXING * this->s_pStreams[i_streamindex].c_pBits[i_bitindex];
			//p_Two.f_Pos[1] = i_offset + S_STYLE_BOXING * this->s_pStreams[i_streamindex].c_pBits[i_bitindex];
			o_pRender->DrawLine(&p_One, &p_Two, & c_Color);
			printf("%d ", i_bitindex);
		}
		printf(" -> %d\n", i_streamindex);
	}
}
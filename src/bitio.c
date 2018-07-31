/*************************************************************
File:
bitio.c

Description:
functions for inputting / outputting bits at a time
*************************************************************/

#include "bitio.h"

static uint8 cur_out_buffer = 0;
static uint8 cur_out_added = 0;
static uint32 cur_in_buffer = 0;
static uint8 cur_in_added = 0;


/*************************************************************
Description:
builds buffer and writes it out to a file when complete
an odd functionality that I don't normally do is to make this
function add multiple bits at a time to the buffer rather
than adding a single bit until all the bits are added.
*************************************************************/

void write_bits
(
FILE * outf,
uint8 bit_length,
uint16 code
)
{
	uint16 masked_code = 0;
	uint8 shift_r = 0;

	while (bit_length > 0)
	{
		if (cur_out_added != 8)
		{
			masked_code = (code & bit_mask_fr_16(bit_length));
			if (bit_length > (8 - cur_out_added))
			{
				shift_r = bit_length - (8 - cur_out_added);
			}
			else{
				shift_r = 0;
			}
			cur_out_buffer = (cur_out_buffer << (bit_length - shift_r)) | (masked_code >> shift_r);
			cur_out_added += (bit_length - shift_r);
			bit_length = shift_r;
		}

		if (cur_out_added == 8)
		{
			fputc(cur_out_buffer, outf);
			cur_out_added = 0;
			cur_out_buffer = 0;
		}
	}
}

/*************************************************************
Description:
flushes the bits at the end if not full byte
*************************************************************/

void flush_bits
(
FILE * outf
)
{
	if (cur_out_added > 0)
	{
		cur_out_buffer <<= (8 - cur_out_added);
		fputc(cur_out_buffer, outf);
	}
}

/*************************************************************
Description:
gets the first bit_length of bits from the input file
*************************************************************/

uint8 read_bits
(
FILE * inf,
uint8 bit_length,
uint16 * bits
)
{
	int16 in_byte = 0;

	while (bit_length > cur_in_added)
	{
		in_byte = fgetc(inf);
		if (in_byte == EOF)
		{
			return(0);
		}
		cur_in_buffer = (cur_in_buffer << 8) | (in_byte & 0xFF);
		cur_in_added += 8;
	}
	*bits = (cur_in_buffer >> (cur_in_added - bit_length)) & bit_mask_fr_32(bit_length);
	cur_in_added -= bit_length;
	return(1);
}
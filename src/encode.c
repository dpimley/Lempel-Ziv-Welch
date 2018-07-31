/*****************************************
File: 
encode.c

Description: 
holds the main functionality
for the lzw compression algorithm
*****************************************/

#include "encode.h"

/*************************************************************
Description:
entry point of the program
*************************************************************/

int main(int argc, char * * argv)
{
	//verify input count
	if (argc != 3)
	{
		printf("Usage: encode <file> <outputfile>\n");
		return EXIT_FAILURE;
	}

	FILE * inf = fopen(argv[1], "rb");

	if (inf == NULL)
	{
		return EXIT_FAILURE;
	}

	FILE * outf = fopen(argv[2], "wb");

	if (outf == NULL)
	{
		return EXIT_FAILURE;
	}

	dict_root * dict;
	init_dict(&dict);

	encode(dict, inf, outf);

	free_dict(dict);
	fclose(inf);
	fclose(outf);

	return EXIT_SUCCESS;
}

/*************************************************************
Description:
main functionality for lzw technique
*************************************************************/

void encode
(
	dict_root * dict,
	FILE * inf,
	FILE * outf
)
{
	int16 in_char = 0;
	uint8 str_build[ENCODE_MAX_STRING_LENGTH];
	uint8 _str_build_tmp[ENCODE_MAX_STRING_LENGTH];
	uint8 bit_length = ENCODE_INIT_BIT_LENGTH;
	uint16 enc_code = 0;
	uint16 cur_code_pos = DICT_INITIAL_ROOT_SZ;

	uint16 a = 0;

	memset(str_build, 0, sizeof(str_build));
	memset(_str_build_tmp, 0, sizeof(_str_build_tmp));

	while (in_char != EOF)
	{
		in_char = fgetc(inf);
		if (in_char == EOF)
		{
			break;
		}

		strncat(_str_build_tmp, &in_char, 1);
		
		
		if (find_node(dict, &enc_code, _str_build_tmp))
		{
			strncat(str_build, &in_char, 1);
		}
		else
		{

			if (enc_code == 523)
			{
				enc_code = enc_code;
			}

			write_bits(outf, bit_length, enc_code);

			insert_node(dict, cur_code_pos, _str_build_tmp);

			memset(str_build, 0, sizeof(str_build));
			memset(_str_build_tmp, 0, sizeof(_str_build_tmp));

			strncpy(str_build, &in_char, 1);
			strncpy(_str_build_tmp, &in_char, 1);
			cur_code_pos++;
			if (bit_repr(cur_code_pos - 1) > bit_length)
			{
				bit_length++;
			}
		}
	}
	find_node(dict, &enc_code, _str_build_tmp);
	write_bits(outf, bit_length, enc_code);
	flush_bits(outf);
}
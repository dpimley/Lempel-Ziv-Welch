/*************************************************************
File:
decode.c

Description:
holds the main functionality for the lzw decompression 
algorithm
*************************************************************/

#include "decode.h"

/*************************************************************
Description:
entry point of the program
*************************************************************/

int main(int argc, char * * argv)
{
	//verify input count
	if (argc != 3)
	{
		printf("Usage: decode <file> <outputfile>\n");
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

	hash_root * root;
	hash_init(&root);
	decode(root, inf, outf);
	hash_free(root);
	fclose(inf);
	fclose(outf);

	return EXIT_SUCCESS;
}

/*************************************************************
Description:
functionality for lzw decode of compressed file
*************************************************************/
void decode
(
hash_root * root,
FILE * inf,
FILE * outf
)
{
	uint16 past_char;
	uint16 cur_char;
	uint16 cur_code_pos = 256;
	uint8 p_str_build[DECODE_MAX_STRING_LENGTH];
	uint8 c_str_build[DECODE_MAX_STRING_LENGTH];
	uint8 p_c_str_build[DECODE_MAX_STRING_LENGTH];
	uint8 bit_length = DECODE_INIT_BIT_LENGTH;
	uint8 eof_read = 0;

	memset(p_str_build, 0, sizeof(p_str_build));
	memset(c_str_build, 0, sizeof(c_str_build));
	memset(p_c_str_build, 0, sizeof(p_c_str_build));

	eof_read = read_bits(inf, bit_length, &cur_char);

	if (!eof_read)
	{
		return;
	}

	fprintf(outf, "%s", root->hash[cur_char].cur_str);

	uint16 a = 0;

	while (eof_read)
	{
		past_char = cur_char;
		eof_read = read_bits(inf, bit_length, &cur_char);

		if (!eof_read)
		{
			return;
		}

		if ((root->hash[cur_char].cur_str[0] != 0
			&& cur_char != 0) 
		|| (root->hash[cur_char].cur_str[0] == 0
			&& cur_char == 0))
		{
			fprintf(outf, "%s", root->hash[cur_char].cur_str);
			memset(p_str_build, 0, sizeof(p_str_build));
			strcpy(p_str_build, root->hash[past_char].cur_str);
			strncpy(c_str_build, root->hash[cur_char].cur_str, 1);
			memset(p_c_str_build, 0, sizeof(p_c_str_build));
			strcpy(p_c_str_build, p_str_build);
			strcat(p_c_str_build, c_str_build);
			hash_insert(root, cur_code_pos, p_c_str_build);
		}
		else
		{
			memset(p_str_build, 0, sizeof(p_str_build));
			memset(c_str_build, 0, sizeof(c_str_build));
			memset(p_c_str_build, 0, sizeof(p_c_str_build));
			strcpy(p_str_build, root->hash[past_char].cur_str);
			strncpy(c_str_build, p_str_build, 1);
			strcpy(p_c_str_build, p_str_build);
			strcat(p_c_str_build, c_str_build);
			fprintf(outf, "%s", p_c_str_build);
			hash_insert(root, cur_code_pos, p_c_str_build);
		}
		cur_code_pos++;
		if (bit_repr(cur_code_pos) > bit_length)
		{
			bit_length++;
		}
	}
}
		
/*************************************************************
File:
dict.h

Description:
holds the header information for dict.c
*************************************************************/

#ifndef _DICT_H
#define	_DICT_H

#include "util.h"
#include <stdlib.h>

#define DICT_INITIAL_CHILDREN   ( 4 )
#define DICT_INITIAL_ROOT_SZ    ( 256 )
#define DICT_CHAR_SEQ_NOT_FOUND ( 65535 )
#define DICT_REALLOC_FACTOR		( 2 )

//#pragma pack(push, 1)

typedef struct dict_node
{
	uint8 cur_char;			/* current character			*/
	uint16 cur_code;		/* current code for char seq	*/
	uint8 child_cnt;		/* number of existing children	*/
	uint8 child_sz;			/* size of allocated array		*/
	uint32 count;			/* number of appearances		*/
	struct dict_node * children;
							/* array of next characters		*/	
} dict_node;

typedef struct dict_root
{
	dict_node * init_dict;	/* holds initial dictionary		*/
} dict_root;

//#pragma pack(pop)

void init_dict
(
	dict_root * * dict
);

uint8 find_node
(
	dict_root * dict,
	uint16 * code,
	char * key
);

void insert_node
(
	dict_root * dict,
	uint16 code,
	char * key
);

void free_dict
(
	dict_root * dict
);

void free_children
(
	dict_node * node
);

#endif /* _DICT_H */
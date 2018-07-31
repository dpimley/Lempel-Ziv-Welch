/*************************************************************
File:
hash.h

Description:
header file for hash functionality
*************************************************************/

#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

#define DECODE_MAX_STRING_LENGTH ( 2048 )
#define DECODE_INIT_BIT_LENGTH ( 9 )

#define DECODE_INIT_HASH_SZ ( 65536 )
//TODO: Fix realloc

#define HASH_REALLOC_FACTOR ( 2 )

typedef struct hash_node
{
	uint8 cur_str[DECODE_MAX_STRING_LENGTH];
} hash_node;

typedef struct hash_root
{
	uint32 hash_sz;
	hash_node * hash;
} hash_root;

void hash_init
(
	hash_root * * root
);

void hash_insert
(
	hash_root * root,
	uint16 ins_code,
	uint8 ins_str[DECODE_MAX_STRING_LENGTH]
);

void hash_free
(
	hash_root * root
);

#endif /* _HASH_H */
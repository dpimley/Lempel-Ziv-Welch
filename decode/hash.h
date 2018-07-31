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

#define DECODE_MAX_STRING_LENGTH ( 128 )
#define DECODE_INIT_BIT_LENGTH ( 9 )

#define DECODE_INIT_HASH_SZ ( 512 )

#define HASH_REALLOC_FACTOR ( 2 )

typedef struct hash_root
{
	uint16 hash_sz;
	hash_node * hash;
} hash_root;

typedef struct hash_node
{
	char cur_str[DECODE_MAX_STRING_LENGTH];
} hash_node;

void hash_init
(
	hash_root * * root
);

void hash_insert
(
	hash_root * root,
	uint16 ins_code,
	char ins_str[DECODE_MAX_STRING_LENGTH]
);

#endif /* _HASH_H */
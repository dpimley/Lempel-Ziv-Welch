/*************************************************************
File:
decode.h

Description:
holds the header information for decode.c
*************************************************************/

#ifndef _DECODE_H
#define _DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitio.h"
#include "hash.h"

#define DECODE_MAX_STRING_LENGTH ( 2048 )
#define DECODE_INIT_BIT_LENGTH ( 9 )

void decode
(
	hash_root * hash,
	FILE * inf,
	FILE * outf
);

#endif /* _DECODE_H */
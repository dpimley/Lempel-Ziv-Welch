/*************************************************************
File:
encode.h

Description:
holds the header information for encode.c
*************************************************************/

#ifndef _ENCODE_H
#define	_ENCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitio.h"
#include "dict.h"

#define ENCODE_MAX_STRING_LENGTH ( 2048 )
#define ENCODE_INIT_BIT_LENGTH ( 9 )

void encode
(
	dict_root * dict,
	FILE * inf,
	FILE * outf
);

#endif /* _ENCODE_H */
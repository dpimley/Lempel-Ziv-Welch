/*************************************************************
File:
bitio.h

Description:
holds the header information for bitio.h
*************************************************************/

#ifndef _BITIO_H
#define _BITIO_H

#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#define bit_mask_fl_8( x ) \
	(0xFF << (8 - ( x )))

#define bit_mask_fr_8( x ) \
	(0xFF >> (8 - ( x )))

#define bit_mask_fl_16( x ) \
	(0xFFFF << (16 - ( x )))

#define bit_mask_fr_16( x ) \
	(0xFFFF >> (16 - ( x )))

#define bit_mask_fl_32( x ) \
	(0xFFFFFFFF << (32 - ( x )))

#define bit_mask_fr_32( x ) \
	(0xFFFFFFFF >> (32 - ( x )))

#define bit_set( x ) \
	((uint16)1 << (x))

#define bit_repr( x )				\
	(((x) & bit_set(15)) ? (16) :	\
	 ((x) & bit_set(14)) ? (15) :	\
	 ((x) & bit_set(13)) ? (14) :	\
	 ((x) & bit_set(12)) ? (13) :	\
	 ((x) & bit_set(11)) ? (12) :	\
	 ((x) & bit_set(10)) ? (11) :	\
	 ((x) & bit_set(9))  ? (10) :	\
	 ((x) & bit_set(8))  ?  (9) :	\
	 ((x) & bit_set(7))  ?  (8) :	\
	 ((x) & bit_set(6))  ?  (7) :	\
	 ((x) & bit_set(5))  ?  (6) :	\
	 ((x) & bit_set(4))  ?  (5) :	\
	 ((x) & bit_set(3))  ?  (4) :	\
	 ((x) & bit_set(2))  ?  (3) :	\
	 ((x) & bit_set(1))  ?  (2) :	\
							(1))	\

void write_bits
(
	FILE * outf,
	uint8 bit_length,
	uint16 code
);

void flush_bits
(
	FILE * outf
);

uint8 read_bits
(
	FILE * inf,
	uint8 bit_length,
	uint16 * bits
);

#endif /* _BITIO_H */
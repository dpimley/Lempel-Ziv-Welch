/*************************************************************
File:
hash.c

Description:
functionality for hash implementation
*************************************************************/

#include "hash.h"

/*************************************************************
Description:
initializes the hash table with an initial amount of entries
*************************************************************/

void hash_init
(
hash_root * * root
)
{
	uint16 i = 0;

	(*root) = (hash_root *)malloc(sizeof(hash_root));
	(*root)->hash = (hash_node *)calloc(DECODE_INIT_HASH_SZ, sizeof(hash_node));
	(*root)->hash_sz = DECODE_INIT_HASH_SZ;

	for (i = 0; i < 256; i++)
	{
		memset((*root)->hash[i].cur_str, 0, sizeof((*root)->hash[i].cur_str));
		(*root)->hash[i].cur_str[0] = i;
	}
}


/*************************************************************
Description:
inserts a hash node into the table
*************************************************************/

void hash_insert
(
	hash_root * root,
	uint16 ins_code,
	uint8 ins_str[DECODE_MAX_STRING_LENGTH]
)
{
	if (ins_code >= root->hash_sz)
	{
		root->hash_sz = root->hash_sz * HASH_REALLOC_FACTOR;
		root->hash = (hash_node *)realloc(root->hash, root->hash_sz);
	}
	memset(root->hash[ins_code].cur_str, 0, sizeof(root->hash[ins_code].cur_str));
	strcpy(root->hash[ins_code].cur_str, ins_str);

}

/*************************************************************
Description:
frees the hash table
*************************************************************/

void hash_free
(
hash_root * root
)
{
	free(root->hash);
	free(root);
}
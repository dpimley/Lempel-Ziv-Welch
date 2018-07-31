/*************************************************************
File:
dict.c

Description:
functions for dictionary to hold chars
and codes for lzw
*************************************************************/

#include "dict.h"

/*************************************************************
Description:
initializes the dictionary and extended dictionary to four
children
*************************************************************/

void init_dict
(
	dict_root * * dict
)
{
	uint16 i;

	(*dict) = (dict_root *)malloc(sizeof(dict_root));
	(*dict)->init_dict = (dict_node *)malloc(DICT_INITIAL_ROOT_SZ * sizeof(dict_node));

	for (i = 0; i < DICT_INITIAL_ROOT_SZ; i++)
	{
		(*dict)->init_dict[i].cur_char = i;
		(*dict)->init_dict[i].cur_code = i;
		(*dict)->init_dict[i].child_cnt = 0;
		(*dict)->init_dict[i].child_sz = DICT_INITIAL_CHILDREN;
		(*dict)->init_dict[i].count = 0;
		(*dict)->init_dict[i].children = (dict_node *)malloc(DICT_INITIAL_CHILDREN * sizeof(dict_node));
	}
}

/*************************************************************
Description:
finds and returns the node with the given key
*************************************************************/

uint8 find_node
(
	dict_root * dict,
	uint16 * code,
	char * key
)
{
	uint16 r_idx = 0;
	uint16 s_idx = 0;
	dict_node cur_pos;

	while (key[r_idx] != 0)
	{
		if (r_idx == 0)
		{
			cur_pos = dict->init_dict[key[r_idx]];
			*code = (uint16)key[r_idx];
		}
		else
		{
			while ((s_idx < cur_pos.child_cnt) && 
				   (key[r_idx] != cur_pos.children[s_idx].cur_char))
			{
				s_idx++;
			}
			if (s_idx < cur_pos.child_cnt)
			{
				cur_pos = cur_pos.children[s_idx];
				*code = cur_pos.cur_code;
			}
			else
			{
				return(0);
			}
		}
		r_idx++;
	}
	return(1);
}

/*************************************************************
Description:
inserts a node into the dictionary with the given code
and key
*************************************************************/

void insert_node
(
	dict_root * dict,
	uint16 code,
	char * key
)
{
	uint16 r_idx = 0;
	uint16 s_idx = 0;

	dict_node * ins_node;

	dict_node * cur_pos;

	while (key[r_idx] != '\0')
	{
		if (r_idx == 0)
		{
			cur_pos = &(dict->init_dict[key[r_idx]]);
		}
		else
		{
			while ((s_idx < cur_pos->child_cnt) &&
				(key[r_idx] != cur_pos->children[s_idx].cur_char))
			{
				s_idx++;
			}
			if (s_idx < cur_pos->child_cnt)
			{
				cur_pos = &(cur_pos->children[s_idx]);
			}
			else if (s_idx >= cur_pos->child_cnt &&
				cur_pos->child_cnt < cur_pos->child_sz)
			{
				ins_node = &(cur_pos->children[s_idx]);
				ins_node->cur_code = code;
				ins_node->cur_char = key[r_idx];
				ins_node->child_cnt = 0;
				ins_node->child_sz = DICT_INITIAL_CHILDREN;
				ins_node->count += 1;
				ins_node->children = (dict_node *)malloc(DICT_INITIAL_CHILDREN * sizeof(dict_node));
				memset(ins_node->children, 0, DICT_INITIAL_CHILDREN * sizeof(dict_node));
				cur_pos->child_cnt++;
				return;
			}
			else if (s_idx >= cur_pos->child_cnt &&
				cur_pos->child_cnt >= cur_pos->child_sz)
			{
				cur_pos->child_sz = cur_pos->child_sz * DICT_REALLOC_FACTOR;
				cur_pos->children = (dict_node *)realloc(cur_pos->children, sizeof(dict_node) * cur_pos->child_sz);
				ins_node = &(cur_pos->children[s_idx]);
				ins_node->cur_code = code;
				ins_node->cur_char = key[r_idx];
				ins_node->child_cnt = 0;
				ins_node->child_sz = DICT_INITIAL_CHILDREN;
				ins_node->count += 1;
				ins_node->children = (dict_node *)malloc(DICT_INITIAL_CHILDREN * sizeof(dict_node));
				memset(ins_node->children, 0, DICT_INITIAL_CHILDREN * sizeof(dict_node));
				cur_pos->child_cnt++;
				return;
			}
		}
		s_idx = 0;
		r_idx++;
	}
}

/*************************************************************
Description:
frees the memory allocated by the dictionary root
*************************************************************/

void free_dict
(
	dict_root * dict
)
{
	uint16 i = 0;

	for (i = 0; i < DICT_INITIAL_ROOT_SZ; i++)
	{
		free_children(&(dict->init_dict[i]));
	}

	free(dict);
}

/*************************************************************
Description:
recursively frees the memory allocated by the node children
*************************************************************/

void free_children
(
	dict_node * node
)
{
	uint16 i = 0;

	if (node->child_cnt == 0)
	{
		free(node->children);
		return;
	}

	for (i = 0; i < node->child_cnt; i++)
	{
		free_children(&(node->children[i]));
	}
	free(node->children);
	return;
}
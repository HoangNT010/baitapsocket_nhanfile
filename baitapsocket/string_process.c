#include "string_process.h"
int Str_len(char* pt_str)
{
	unsigned int len = 0;
	while (*pt_str != '\0')
	{
		len++;
		pt_str++;
	}
	return len;
}

int find_SubStr_Position(char* pt_str, char* pt_search, int len_target)
{

	int i = 0;
	int position = 0;
	while (pt_str[i] != '\0')
	{
		int j = 0;
		if (*(pt_search + j) == *(pt_str + i))
		{
			while (*(pt_search + j) == *(pt_str + i) && *(pt_str + i) != '\0')
			{
				i++;
				j++;
			}
			if (j == len_target)
			{
				position = position + i - j;
			}
		}
		i++;
	}
	return position;
}

int getValue(char* pt_str, int pos, int len)
{
	int num = 0;
	int j = pos + len;

	while (pt_str[j] != '\0')
	{
		if (pt_str[j] >= '0' && pt_str[j] <= '9')
		{
			num = num * 10 + (pt_str[j] - '0');
		}
		j++;
	}

	return num;
}
# -*- coding: utf-8 -*-
#include <stddef.h>

int mystrlen(char *str)
{
	int i = 0;
	while (str[i] != NULL)
	{
		i++;
	}
	return i;
}

char *mystrcpy(char *toStr, char *fromStr)
{
	char *start;
	start = toStr;

	do
	{
		*toStr = *fromStr;
		toStr++;
		fromStr++;
	} while (*toStr = *fromStr);

	return start;
}

char *mystrcat(char *str1, char *str2)
{
	int i = 0;
	while (!(str1[i] == '\0'))
	{
		i++;
	}
	int j = 0;

	while (str2[j] != '\0')
	{
		str1[i] = str2[j];
		i++;
		j++;
	}

	return str1;
}

char *mystrchr(char *str, char c)
{
	int i = 0;
	while (str[i] != NULL)
	{
		if (str[i] == c)
		{
			return str;
		}
		else
		{
			str++;
		}
	}
	return NULL;
}

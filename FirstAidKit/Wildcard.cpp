//Copyright (C) 1996 - 2002 Florian Schintke
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "stdafx.h"
#include "Wildcard.h"

int Wildcard::wildcardfit(LPCTSTR wildcard,  LPCTSTR test)
{
	int fit = 1;

	for (; (TEXT('\000') != *wildcard) && (1 == fit) && (TEXT('\000') != *test); wildcard++)
	{
		switch (*wildcard)
		{
		case TEXT('['):
			wildcard++; /* leave out the opening square bracket */ 
			fit = set (&wildcard, &test);
			/* we don't need to decrement the wildcard as in case */
			/* of asterisk because the closing ] is still there */
			break;
		case TEXT('?'):
			test++;
			break;
		case TEXT('*'):
			fit = asterisk (&wildcard, &test);
			/* the asterisk was skipped by asterisk() but the loop will */
			/* increment by itself. So we have to decrement */
			wildcard--;
			break;
		default:
			fit = (int) (*wildcard == *test);
			test++;
		}
	}
	while ((*wildcard == TEXT('*')) && (1 == fit)) 
		/* here the teststring is empty otherwise you cannot */
		/* leave the previous loop */ 
		wildcard++;
	return (int) ((1 == fit) && (TEXT('\0') == *test) && (TEXT('\0') == *wildcard));
}

int Wildcard::set(LPCTSTR *wildcard, LPCTSTR *test)
{
	int fit = 0;
	int negation = 0;
	int at_beginning = 1;

	if ('!' == **wildcard)
	{
		negation = 1;
		(*wildcard)++;
	}
	while ((TEXT(']') != **wildcard) || (1 == at_beginning))
	{
		if (0 == fit)
		{
			if ((TEXT('-') == **wildcard) 
				&& ((*(*wildcard - 1)) < (*(*wildcard + 1)))
				&& (TEXT(']') != *(*wildcard + 1))
				&& (0 == at_beginning))
			{
				if (((**test) >= (*(*wildcard - 1)))
					&& ((**test) <= (*(*wildcard + 1))))
				{
					fit = 1;
					(*wildcard)++;
				}
			}
			else if ((**wildcard) == (**test))
			{
				fit = 1;
			}
		}
		(*wildcard)++;
		at_beginning = 0;
	}
	if (1 == negation)
		/* change from zero to one and vice versa */
		fit = 1 - fit;
	if (1 == fit) 
		(*test)++;

	return (fit);
}

int Wildcard::asterisk (LPCTSTR *wildcard, LPCTSTR *test)
{
	/* Warning: uses multiple returns */
	int fit = 1;

	/* erase the leading asterisk */
	(*wildcard)++; 
	while ((TEXT('\000') != (**test))
		&& ((TEXT('?') == **wildcard) 
		|| (TEXT('*') == **wildcard)))
	{
		if (TEXT('?') == **wildcard) 
			(*test)++;
		(*wildcard)++;
	}
	/* Now it could be that test is empty and wildcard contains */
	/* aterisks. Then we delete them to get a proper state */
	while (TEXT('*') == (**wildcard))
		(*wildcard)++;

	if ((TEXT('\0') == (**test)) && (TEXT('\0') != (**wildcard)))
		return (fit = 0);
	if ((TEXT('\0') == (**test)) && (TEXT('\0') == (**wildcard)))
		return (fit = 1); 
	else
	{
		/* Neither test nor wildcard are empty!          */
		/* the first character of wildcard isn't in [*?] */
		if (0 == wildcardfit(*wildcard, (*test)))
		{
			do 
			{
				(*test)++;
				/* skip as much characters as possible in the teststring */
				/* stop if a character match occurs */
				while (((**wildcard) != (**test)) 
					&& (TEXT('[')  != (**wildcard))
					&& (TEXT('\0') != (**test)))
					(*test)++;
			}
			while (((TEXT('\0') != **test))? 
				(0 == wildcardfit (*wildcard, (*test))) 
				: (0 != (fit = 0)));
		}
		if ((TEXT('\0') == **test) && (TEXT('\0') == **wildcard))
			fit = 1;
		return (fit);
	}
}
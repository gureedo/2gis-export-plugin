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

#pragma once

// Implementation of the UN*X wildcards
// Supported wild-characters: '*', '?'; sets: [a-z], '!' negation
// Examples:
//       '[a-g]l*i?n' matches 'florian'
//       '[!abc]*e' matches 'smile'
//       '[-z] matches 'a'

class Wildcard
{
public:
	// This function implements the UN*X wildcards and returns:
	// 0 - if *wildcard does not match *test
	// 1 - if *wildcard matches *test
	static int wildcardfit (LPCTSTR wildcard, LPCTSTR test);

private:
	// Scans a set of characters and returns 0 if the set mismatches at this
	// position in the teststring and 1 if it is matching
	// wildcard is set to the closing ] and test is unmodified if mismatched
	// and otherwise the char pointer is pointing to the next character
	static int set (LPCTSTR *wildcard, LPCTSTR *test);

	// Scans an asterisk
	static int asterisk (LPCTSTR *wildcard, LPCTSTR *test);
};
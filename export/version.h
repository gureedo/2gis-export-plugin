// Copyright (C) 2012 gureedo
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma once

#define _CSTR(x) _T(#x)
#define CSTR(x) _CSTR(x)

#define PLUGIN_VER_MJR 0
#define PLUGIN_VER_MNR 1

#define PLUGIN_VER_STR CSTR(PLUGIN_VER_MJR) _T(".") CSTR(PLUGIN_VER_MNR)
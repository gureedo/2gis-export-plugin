#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <atlwin.h>

#import "libid:7AA02C95-0B4A-43aa-92D8-BA40511A7F3F" rename("RemoveDirectory", "GrymRemoveDirectory")

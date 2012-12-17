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

#include "stdafx.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "PluginInfo.h"

CPluginInfo g_pi;

GrymCore::IMapCoordinateTransformationGeoPtr CPluginInfo::coordinateTranslator() const
{
	IUnknownPtr pTrans = baseView->Frame->Map->CoordinateTransformation;
	GrymCore::IMapCoordinateTransformationGeoPtr pGEO;
	if ( pTrans ) {
		pTrans->QueryInterface(__uuidof(GrymCore::IMapCoordinateTransformationGeo), (void**)&pGEO);
		if ( !pGEO )
			throw std::wstring(_T("Can't query IMapCoordinateTransformationGeo"));
	}

	return pGEO;
}

std::wstring CPluginInfo::decimal2degree( double x )
{
	std::wstringstream ss;
	int d = static_cast<int>(x);
	x = (x-d)*60;
	int m = static_cast<int>(x);
	x = (x-m)*60;
	int s = static_cast<int>(x);
	x = (x-s)*100;
	int ds = static_cast<int>(x);
	ss << std::setfill(_T('0'));
	ss << std::setw(2) << d << _T('°');
	ss << std::setw(2) << m << _T('\'');
	ss << std::setw(2) << s << _T(',');
	ss << std::setw(2) << ds << _T('"');

	return ss.str();
}

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
#include <sstream>
#include "ExtendedInfoBlock.h"
#include "PluginInfo.h"

GrymCore::IMapInfoControllerPtr CExtendedInfoBlock::CreateInstance()
{
	ATL::CComObject<CExtendedInfoBlock> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<CExtendedInfoBlock>::CreateInstance(&obj));
	GrymCore::IMapInfoControllerPtr rv = obj;
	ATLASSERT(NULL != rv);

	return rv;
}

STDMETHODIMP CExtendedInfoBlock::raw_Check( GrymCore::IFeature *pFeature, VARIANT_BOOL *pVal )
{

	try {
		if ( !pVal )
			return E_POINTER;

		*pVal = VARIANT_TRUE;

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP CExtendedInfoBlock::get_Title( BSTR *pVal )
{
	try {
		if ( !pVal )
			return E_POINTER;

		*pVal = _bstr_t(OLESTR("EXPORT")).Detach();

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP CExtendedInfoBlock::raw_Fill( GrymCore::IFeature *pFeature, GrymCore::ICalloutTab *pTab )
{
	try {
		GrymCore::IMapCoordinateTransformationGeoPtr geoTrans = g_pi.coordinateTranslator();
		GrymCore::IMapPointPtr point;
		std::wstringstream ss;

		// point coordinates
		HWND hWnd = (HWND)g_pi.baseView->Frame->Map->HWindow;
		POINT curPos;
		::GetCursorPos(&curPos);
		::ScreenToClient(hWnd, &curPos);
		GrymCore::IDevPointPtr devPtr = g_pi.baseView->Factory->CreateDevPoint(curPos.x, curPos.y);
		GrymCore::IMapDevicePtr devMap = g_pi.baseView->Frame->Map;
		GrymCore::IMapPointPtr mapPtr = devMap->DeviceToMap(devPtr);
		point = geoTrans->LocalToGeo(mapPtr);

		ss << _T("<b>Point coordinates</b><br>");
		ss << g_pi.decimal2degree(point->Y) << _T(" ") << g_pi.decimal2degree(point->X);

		// selected object coordinates
		static const _bstr_t grym_map_building(_T("grym_map_building"));
		static const _bstr_t grym_map_rwstation(_T("grym_map_rwstation"));
		static const _bstr_t grym_map_stationbay(_T("grym_map_stationbay"));
		static const _bstr_t grym_map_sight(_T("grym_map_sight"));
		GrymCore::IDataRowPtr row = pFeature;
		
		if ( row->GetType() == grym_map_building || row->GetType() == grym_map_rwstation ||
				row->GetType() == grym_map_stationbay || row->GetType() == grym_map_sight ) {
			ss << _T("<hr><b>Object coordinates</b><br>");
			point = geoTrans->LocalToGeo(pFeature->CenterPoint);
			ss << g_pi.decimal2degree(point->Y) << _T(" ") << g_pi.decimal2degree(point->X);
		}
		
		pTab->put_Text(_bstr_t(ss.str().c_str()));

		return S_OK;
	} catch (...) {
	}
		return E_FAIL;
}

STDMETHODIMP CExtendedInfoBlock::raw_OnTabAction( GrymCore::ICalloutTab *pTab, BSTR bsActionID )
{
	return S_OK;
}
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
#include "resource.h"
#include "DlgExport.h"
#include "PluginInfo.h"

using namespace std;

CDlgExport::CDlgExport()
{
	// organizations tables
	m_tables.push_back(TableInfo(_T("grym_org"), _T("Organization")));
	m_tables.push_back(TableInfo(_T("grym_rub1"), _T("Rubric 1")));
	m_tables.push_back(TableInfo(_T("grym_rub2"), _T("Rubric 2")));
	m_tables.push_back(TableInfo(_T("grym_rub3"), _T("Rubric 3")));

	// map tables
	m_tables.push_back(TableInfo(_T("grym_map_building"), _T("Buildings")));
	m_tables.push_back(TableInfo(_T("grym_map_street"), _T("Streets")));
	m_tables.push_back(TableInfo(_T("grym_map_district"), _T("Disctincts")));
	m_tables.push_back(TableInfo(_T("grym_map_microdistrict"), _T("Microdistincts")));
	m_tables.push_back(TableInfo(_T("grym_map_city"), _T("Cities (secondrary)")));
	m_tables.push_back(TableInfo(_T("grym_map_rwstation"), _T("Railroad stations")));
	m_tables.push_back(TableInfo(_T("grym_map_stationbay"), _T("Station bays")));
	m_tables.push_back(TableInfo(_T("grym_map_territory"), _T("Territories")));
	m_tables.push_back(TableInfo(_T("grym_map_sight"), _T("Sights")));

	// common tables
	m_tables.push_back(TableInfo(_T("grym_city"), _T("Cities (common)")));
	m_tables.push_back(TableInfo(_T("grym_street"), _T("Streets (common)")));
	m_tables.push_back(TableInfo(_T("grym_address"), _T("Address (common)")));
}

LRESULT CDlgExport::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_wndTableList.Attach(GetDlgItem(IDC_TABLES));

	m_wndTableList.AddColumn(_T("Table"), 0);
	m_wndTableList.AddColumn(_T("Count"), 1);
	m_wndTableList.AddColumn(_T("Description"), 2);

	for ( auto it=m_tables.cbegin(); it != m_tables.cend(); ++it ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(_bstr_t(it->name.c_str()));
		wstringstream wss;

		wss << table->GetRecordCount();
		wstring recCountStr = wss.str();

		m_wndTableList.AddItem(0, 0, it->name.c_str());
		m_wndTableList.AddItem(0, 1, recCountStr.c_str());
		m_wndTableList.AddItem(0, 2, it->description.c_str());
	}

	return TRUE;
}

LRESULT CDlgExport::OnCancel( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	EndDialog(wID);
	return 0;
}
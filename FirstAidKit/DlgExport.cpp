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
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include "DlgExport.h"
#include "PluginInfo.h"

using namespace std;

CDlgExport::CDlgExport()
{
	// organizations tables
	m_tables.push_back(new TableInfo(_T("grym_org"), _T("Organization"), false));
	m_tables.push_back(new TableInfo(_T("grym_org_fil"), _T("Organization suboffices"), true));
	m_tables.push_back(new TableInfo(_T("grym_rub1"), _T("Rubric 1"), false));
	m_tables.push_back(new TableInfo(_T("grym_rub2"), _T("Rubric 2"), false));
	m_tables.push_back(new TableInfo(_T("grym_rub3"), _T("Rubric 3"), false));

	// map tables
	m_tables.push_back(new TableInfo(_T("grym_map_building"), _T("Buildings"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_street"), _T("Streets"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_district"), _T("Disctincts"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_microdistrict"), _T("Microdistincts"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_city"), _T("Cities (secondrary)"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_rwstation"), _T("Railroad stations"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_stationbay"), _T("Station bays"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_territory"), _T("Territories"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_sight"), _T("Sights"), false));

	// common tables
	m_tables.push_back(new TableInfo(_T("grym_city"), _T("Cities (common)"), false));
	m_tables.push_back(new TableInfo(_T("grym_street"), _T("Streets (common)"), false));
	m_tables.push_back(new TableInfo(_T("grym_address"), _T("Address (common)"), false));
}

CDlgExport::~CDlgExport()
{
	for_each(m_tables.begin(), m_tables.end(), [] (TableInfo *ti) { delete ti; });
	m_tables.clear();
	// WTL bug?
	m_hWnd = NULL;
}

LRESULT CDlgExport::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_wndTableList.SubclassWindow(GetDlgItem(IDC_TABLES));
	m_wndLog.Attach(GetDlgItem(IDC_LOG));

	m_wndTableList.AddColumn(_T("Name"), 0, -1, LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM, LVCFMT_LEFT);
	m_wndTableList.AddColumn(_T("Description"), 1, -1, LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM, LVCFMT_LEFT);
	m_wndTableList.AddColumn(_T("Count"), 2, -1, LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM, LVCFMT_RIGHT);

	LVCOLUMN lvc = { 0 };
	lvc.mask = LVCF_WIDTH;
	lvc.cx = 150;
	m_wndTableList.SetColumn(0, &lvc);
	lvc.cx = 150;
	m_wndTableList.SetColumn(1, &lvc);
	lvc.cx = 100;
	m_wndTableList.SetColumn(2, &lvc);

	for ( auto it = m_tables.cbegin(); it != m_tables.cend(); ++it ) {
		TableInfo *info = *it;

		wstring recCountStr;
		if ( !info->isVirtual ) {
			try {
				wstringstream ss;
				GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(info->name.c_str());
				ss << table->GetRecordCount();
				recCountStr = ss.str();
			} catch (...) {
				recCountStr = _T("0");
			}
		} else {
			recCountStr = _T("0");
		}

		int idx = m_wndTableList.AddItem(0, 0, info->name.c_str());
		m_wndTableList.AddItem(0, 1, info->description.c_str());
		m_wndTableList.AddItem(0, 2, recCountStr.c_str());
		m_wndTableList.SetItemData(idx, (DWORD_PTR)info);
		m_wndTableList.SetCheckState(idx, TRUE);
	}

	return TRUE;
}

LRESULT CDlgExport::OnCancel( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	m_wndTableList.UnsubclassWindow();
	m_wndLog.Detach();

	EndDialog(wID);
	return 0;
}

LRESULT CDlgExport::OnSelectExportFolder( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	CFolderDialog dlgFolder;

	if ( dlgFolder.DoModal(*this) == IDOK ) {
		SetDlgItemText(IDC_DSTDIR, dlgFolder.GetFolderPath());
	}

	return 0;
}

LRESULT CDlgExport::OnExport( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	wstring logStr;
	CString bufStr;

	::EnableWindow(GetDlgItem(IDC_BTNEXPORT), FALSE);
	::EnableWindow(GetDlgItem(IDCANCEL), FALSE);
	::EnableWindow(GetDlgItem(IDC_TABLES), FALSE);
	m_wndLog.ResetContent();

	GetDlgItemText(IDC_DSTDIR, bufStr);
	wstring dstDir = bufStr;

	if ( dstDir.empty() ) {
		m_wndLog.AddString(_T("Destination folder not selected."));
		return 0;
	}

	if ( *dstDir.rbegin() != _T('\\') )
		dstDir += _T('\\');

	int tableIdx = -1;
	while ( (tableIdx = m_wndTableList.GetNextItem(tableIdx, LVNI_ALL)) != -1 ) {
		if ( !m_wndTableList.GetCheckState(tableIdx) )
			continue;

		TableInfo *info = (TableInfo *)m_wndTableList.GetItemData(tableIdx);

		m_wndTableList.SelectItem(tableIdx);
		logStr = _T("Processing table ");
		logStr += info->name;
		m_wndLog.AddString(logStr.c_str());

		wstring csvFileName = dstDir + info->name + _T(".csv");

		try {
			exportTable(info->name, csvFileName);
		} catch(wofstream::failure e) {
			logStr = _T("Error: ");
			logStr += CA2W(e.what());
			m_wndLog.AddString(logStr.c_str());
		} catch (...) {
			m_wndLog.AddString(_T("Unknown error occured!"));
		}
	}

	::EnableWindow(GetDlgItem(IDC_BTNEXPORT), TRUE);
	::EnableWindow(GetDlgItem(IDC_TABLES), TRUE);
	::EnableWindow(GetDlgItem(IDCANCEL), TRUE);

	return 0;
}

void CDlgExport::exportTable( const std::wstring &tableName, const std::wstring &outFile ) const
{
	locale utf8_locale(locale("", locale::ctype), new codecvt_utf8<wchar_t, 0x10ffff, generate_header>);
	wofstream csvStream(outFile, ios::out|ios::trunc);
	csvStream.imbue(utf8_locale);

	if ( tableName == _T("grym_org") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_org"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("org_id;org_stable_id;org_name") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			csvStream << idx
				<< _T(";")
				<< (int)row->GetValue(OLESTR("stable_id"))
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("name"))
				<< endl;
		}
	}

	// grym_org_fil

	else if ( tableName == _T("grym_rub1") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_rub1"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("rub1_id;rub1_name") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			csvStream << idx
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("name"))
				<< endl;
		}
	}

	else if ( tableName == _T("grym_rub2") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_rub2"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("rub2_id;rub2_name;rub1_id") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			GrymCore::IDataRowPtr parentRow = row->GetValue(OLESTR("parent"));
			csvStream << idx
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("name"))
				<< _T(";")
				<< parentRow->Index
				<< endl;
		}
	}

	else if ( tableName == _T("grym_rub3") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_rub3"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("rub3_id;rub3_name;rub2_id") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			GrymCore::IDataRowPtr parentRow = row->GetValue(OLESTR("parent"));
			csvStream << idx
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("name"))
				<< _T(";")
				<< parentRow->Index
				<< endl;
		}
	}

	// grym_map_building
	// grym_map_street
	// grym_map_district
	// grym_map_microdistrict
	// grym_map_city
	// grym_map_rwstation
	// grym_map_stationbay
	// grym_map_territory
	// grym_map_sight

	else if ( tableName == _T("grym_city") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_city"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("city_id;city_name;type_name;type_name_abbr") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			csvStream << idx
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("name"))
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("type_name"))
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("type_name_abbr"))
				<< endl;
		}
	}

	else if ( tableName == _T("grym_street") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_street"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("street_id;street_name;city_id;map_street_id") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			GrymCore::IDataRowPtr cityRow = row->GetValue(OLESTR("city"));
			csvStream << idx
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("name"))
				<< _T(";")
				<< cityRow->Index
				<< _T(";");
			try {
				GrymCore::IDataRowPtr mapStreetRow = row->GetValue(OLESTR("feature"));
				csvStream << mapStreetRow->Index;
			} catch (...) {
			}
			csvStream << endl;
		}
	}

	else if ( tableName == _T("grym_address") ) {
		GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(OLESTR("grym_address"));
		long count = table->GetRecordCount();
		long idx = 0;

		csvStream << _T("address_id;address_number;street_id;map_building_id") << endl;

		while ( ++idx <= count ) {
			GrymCore::IDataRowPtr row = table->GetRecord(idx);
			GrymCore::IDataRowPtr streetRow = row->GetValue(OLESTR("street"));
			csvStream << idx
				<< _T(";")
				<< (_bstr_t)row->GetValue(OLESTR("number"))
				<< _T(";")
				<< streetRow->Index
				<< _T(";");
			try {
				GrymCore::IDataRowPtr mapBuildingRow = row->GetValue(OLESTR("feature"));
				csvStream << mapBuildingRow->Index;
			} catch (...) {
			}
			csvStream << endl;
		}
	}

	csvStream.close();
}

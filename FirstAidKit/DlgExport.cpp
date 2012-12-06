#include "stdafx.h"
#include "resource.h"
#include "DlgExport.h"

LRESULT CDlgExport::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CDlgExport::OnCancel( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	EndDialog(wID);
	return 0;
}

LRESULT CDlgExport::OnOK( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	EndDialog(wID);
	return 0;
}

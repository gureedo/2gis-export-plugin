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

#include "StdAfx.h"
#include "resource.h"
#include "PluginImpl.h"
#include "Util.h"
#include "OrgSearchControl.h"
#include "OrgDirectoryCustomController.h"
#include "CmdExport.h"
#include "PluginInfo.h"
#include "ExtendedInfoBlock.h"
#include "version.h"

GrymCore::IGrymPluginPtr CPluginImpl::CreateInstance()
{
	ATL::CComObject<CPluginImpl> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<CPluginImpl>::CreateInstance(&obj));

	return obj;
}

STDMETHODIMP CPluginImpl::raw_Initialize( GrymCore::IGrym *pRoot, GrymCore::IBaseViewThread *pBaseView )
{
	try {
		g_pi.grymApp = pRoot;
		g_pi.baseView = pBaseView;

		GrymCore::IStdDirectoryCustomControllerContainerPtr controllerContainer =
			g_pi.baseView->Frame->DirectoryCollection->GetDirectory(OLESTR("Grym.DirPage.Org"));

		customDirController_ = COrgDirectoryCustomController::CreateInstance();
		controllerContainer->RegisterController(customDirController_);

		GrymCore::IBaseViewFramePtr baseViewFrame = g_pi.baseView->GetFrame();
		GrymCore::IRibbonBarPtr ribbonBar = baseViewFrame->GetMainRibbonBar();

		// create own tab
		static const _bstr_t exportTabTag(_T("Export.MainTab"));
		static const _bstr_t exportTabPlacementCode(_T("3000Export:0"));
		static const _bstr_t exportTabTitle(_T("EXPORT"));
		GrymCore::IRibbonTabPtr exportTab = ribbonBar->CreateTab(exportTabTag, exportTabPlacementCode,exportTabTitle);

		//////////////////////////////////////////////////////////////////////////
		// Search group
		//////////////////////////////////////////////////////////////////////////
		static const _bstr_t searchGroupTag(_T("Export.MainTab.SearchGroup"));
		static const _bstr_t searchGroupPlacementCode(_T("0001SearchGroup:0"));
		static const _bstr_t searchGroupTitle(_T("Organization search"));
		searchGroup_ = exportTab->CreateGroup(GrymCore::RibbonGroupTypeSearch,
			searchGroupTag, searchGroupPlacementCode, searchGroupTitle);

		searchGroup_->SetClearButtonTooltips(
			OLESTR("Очистить"),
			OLESTR("Нечего очищать!"));
		searchGroup_->SetSearchButtonTooltips(
			OLESTR("Будет выполнен поиск по подстроке"),
			OLESTR("Требуется указать параметр для поиска"));
		searchGroup_->SetQueryDescription(
			OLESTR("Поиск по подсроке в организации"),
			OLESTR("Вы искали:"));

		ctrlSearch_ = COrgSearchControl::CreateInstance();
		GrymCore::IControlSetPtr(searchGroup_)->AddControl(ctrlSearch_);

		//////////////////////////////////////////////////////////////////////////
		// Tools group
		//////////////////////////////////////////////////////////////////////////
		static const _bstr_t toolsGroupTag(_T("Export.MainTab.ToolsGroup"));
		static const _bstr_t toolsGroupPlacementCode(_T("0002ToolsGroup:0"));
		static const _bstr_t toolsGroupTitle(_T("Tools"));
		toolsGroup_ = exportTab->CreateGroup(GrymCore::RibbonGroupTypeSimple,
			toolsGroupTag, toolsGroupPlacementCode, toolsGroupTitle);

		// export button
		cmdExport_ = CCmdExport::CreateInstance();
		GrymCore::IControlSetPtr(toolsGroup_)->AddControl(cmdExport_);

		//////////////////////////////////////////////////////////////////////////
		// Extended info block
		//////////////////////////////////////////////////////////////////////////
		GrymCore::IMapInfoControllerPtr infoBlock = CExtendedInfoBlock::CreateInstance(); 
		g_pi.baseView->Frame->Map->MapInfoControllers->AddController(infoBlock);

		return S_OK;
	} catch(...) {
	}

	return E_FAIL;
}

STDMETHODIMP CPluginImpl::raw_Terminate()
{
	try {
		if ( NULL != customDirController_ ) {
			GrymCore::IStdDirectoryCustomControllerContainerPtr controllerContainer =
				g_pi.baseView->Frame->DirectoryCollection->GetDirectory(OLESTR("Grym.DirPage.Org"));
			controllerContainer->UnregisterController(customDirController_);
		}
		
		if ( NULL != searchGroup_ && NULL != ctrlSearch_ )
			GrymCore::IControlSetPtr(searchGroup_)->RemoveControl(ctrlSearch_);
		
		if ( NULL != toolsGroup_ && NULL != cmdExport_ )
			GrymCore::IControlSetPtr(searchGroup_)->RemoveControl(cmdExport_);

		
		ctrlSearch_ = NULL;
		cmdExport_ = NULL;
		searchGroup_ = NULL;
		toolsGroup_ = NULL;
		customDirController_ = NULL;
		g_pi.baseView = NULL;
		g_pi.grymApp = NULL;
	} catch(...) {
	}

	return S_OK;
}

STDMETHODIMP CPluginImpl::get_XMLInfo( BSTR *pVal )
{
	try {
		if ( !pVal )
			return E_POINTER;
		*pVal = 0;

		static const _bstr_t data(
			OLESTR("<grym_plugin_info>")
				OLESTR("<name>Export</name>")
				OLESTR("<description>Blip-blop! Version") PLUGIN_VER_STR OLESTR("</description>")
				OLESTR("<copyright>gureedo, 2012, Freeware</copyright>")
				OLESTR("<tag>EXPORtPLUGIN</tag>")
				OLESTR("<supported_languages>")
					OLESTR("<language>*</language>")
				OLESTR("</supported_languages>")
				OLESTR("<requirements>")
					OLESTR("<requirement_api>API-1.4</requirement_api>")
				OLESTR("</requirements>")
			OLESTR("</grym_plugin_info>")
		);
	
		*pVal = data.copy();

		return S_OK;
	} catch(...) {
	}

	return E_FAIL;
}

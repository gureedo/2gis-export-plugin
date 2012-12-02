#include "StdAfx.h"
#include "PluginImpl.h"
#include "OrgSearchControl.h"
#include "OrgDirectoryCustomController.h"

GrymCore::IGrymPluginPtr CPluginImpl::CreateInstance()
{
	ATL::CComObject<CPluginImpl> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<CPluginImpl>::CreateInstance(&obj));

	return obj;
}

STDMETHODIMP CPluginImpl::raw_Initialize(GrymCore::IGrym *pRoot, GrymCore::IBaseViewThread *pBaseView)
{
	try
	{
		grymAppPtr_ = pRoot;
		baseViewPtr_ = pBaseView;

		GrymCore::IStdDirectoryCustomControllerContainerPtr controllerContainer =
			baseViewPtr_->Frame->DirectoryCollection->GetDirectory(OLESTR("Grym.DirPage.Org"));

		customDirController_ = COrgDirectoryCustomController::CreateInstance();
		controllerContainer->RegisterController(customDirController_);

		GrymCore::IBaseViewFramePtr baseViewFrame = baseViewPtr_->GetFrame();
		GrymCore::IRibbonBarPtr ribbonBar = baseViewFrame->GetMainRibbonBar();

		// create own tab
		static const _bstr_t firstAidTabTag(_T("FirstAidKit.MainTab"));
		static const _bstr_t firstAidTabPlacementCode(_T("3000FirstAidKit:0"));
		static const _bstr_t firstAidTabTitle(_T("First Aid Kit"));
		GrymCore::IRibbonTabPtr firstAidTab = ribbonBar->CreateTab(firstAidTabTag, 
			firstAidTabPlacementCode,firstAidTabTitle);

		// create search group
		static const _bstr_t searchGroupTag(_T("FirstAidKit.MainTab.SearchGroup"));
		static const _bstr_t searchGroupPlacementCode(_T("0001SearchGroup:0"));
		static const _bstr_t searchGroupTitle(_T("Organization search"));
		searchGroup_ = firstAidTab->CreateGroup(GrymCore::RibbonGroupTypeSearch,
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

		ControlAppearanceParams appearance;
		appearance.tag = OLESTR("FirstAidKit.MainTab.SearchControl");
		appearance.placement_code =
			OLESTR("<control_pos>")
				OLESTR("<size min_width=\"150\" max_width=\"300\" height_in_rows=\"1\" />") 
				OLESTR("<position column_id=\"100SearchGroup\" row_id=\"500MyRowByID\" order_in_row=\"1\" />")
			OLESTR("</control_pos>");

		searchControl_ = COrgSearchControl::CreateInstance(appearance,	baseViewPtr_->Factory);
		GrymCore::IControlSetPtr(searchGroup_)->AddControl(searchControl_);

		return S_OK;
	} catch(...){}
	return E_FAIL;
}

STDMETHODIMP CPluginImpl::raw_Terminate()
{
	try
	{
		if ( NULL != customDirController_ ) {
			GrymCore::IStdDirectoryCustomControllerContainerPtr controllerContainer =
				baseViewPtr_->Frame->DirectoryCollection->GetDirectory(OLESTR("Grym.DirPage.Org"));
			controllerContainer->UnregisterController(customDirController_);
		}
		if ( searchGroup_ != NULL && searchControl_ != NULL )
			GrymCore::IControlSetPtr(searchGroup_)->RemoveControl(searchControl_);

		searchControl_ = NULL;
		searchGroup_ = NULL;
		customDirController_ = NULL;
		baseViewPtr_ = NULL;
		grymAppPtr_ = NULL;

	}catch(...){}
	return S_OK;
}

STDMETHODIMP CPluginImpl::get_XMLInfo(BSTR *pVal)
{
	try
	{
		if (!pVal)
		{
			return E_POINTER;
		}
		*pVal = 0;

		static const _bstr_t data(OLESTR("<grym_plugin_info>")
			OLESTR("<name>First Aid Kit</name>")
			OLESTR("<description>DESCRIPTION HERE!</description>")
			OLESTR("<copyright>gureedo, 2012, Freeware</copyright>")
			OLESTR("<tag>FIRSTAIDKITPLUGIN</tag>")
			OLESTR("<supported_languages>")
			OLESTR("<language>ru</language>")
			OLESTR("<language>en</language>")
			OLESTR("</supported_languages>")
			OLESTR("<requirements>")
			OLESTR("<requirement_api>API-1.4</requirement_api>")
			OLESTR("</requirements>")
			OLESTR("</grym_plugin_info>"));
	
		*pVal = data.copy();

		return S_OK;
	}catch(...){}
	return E_FAIL;
}


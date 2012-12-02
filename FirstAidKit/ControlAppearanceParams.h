#pragma once

struct ControlAppearanceParams
{
	_bstr_t placement_code;
	_bstr_t tag;
	_bstr_t caption;
	_bstr_t description;
	IUnknownPtr icon;

	ControlAppearanceParams()
	{
		placement_code = _T("");
		tag = _T("");
		caption = _T("");
		description = _T("");
		icon = NULL;
	}
};
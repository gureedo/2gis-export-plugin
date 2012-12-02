#include "StdAfx.h"
#include "ControlBase.h"

ControlBase::ControlBase()
	: accelerator_(0)
{
}

ControlBase::~ControlBase()
{
}

void ControlBase::SetAccelerator(DWORD accelerator) {
	accelerator_ = accelerator; }

HRESULT WINAPI ControlBase::ICommandAcceleratorQIFunc(void* pv, REFIID /*riid*/, LPVOID* ppv, DWORD /*dw*/)
{
	ControlBase *pThis = static_cast<ControlBase *>(pv);
	*ppv = NULL;
	if (pThis->accelerator_)
	{
		*ppv = static_cast<GrymCore::ICommandAccelerator *>(pThis);
		pThis->AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

STDMETHODIMP ControlBase::get_Accelerator(LONG *pVal)
{
	if (!pVal)
		return E_POINTER;
	*pVal = accelerator_;
	return S_OK;
}
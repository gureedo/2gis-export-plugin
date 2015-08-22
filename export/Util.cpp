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
#include "Util.h"

namespace Util {

GrymCore::IRasterPtr LoadResourceRaster( GrymCore::IGrymObjectFactory *pFactory, UINT_PTR rcid_png )
{
	ATLASSERT(NULL != pFactory);

	GrymCore::IRasterPtr rv;

	HRSRC hResource = ::FindResource(ATL::_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(rcid_png), _T("PNG"));
	ATLASSERT(NULL != hResource);
	if ( NULL != hResource ) {
		HGLOBAL hGlobal = ::LoadResource(ATL::_AtlBaseModule.GetResourceInstance(), hResource);
		ATLASSERT(NULL != hGlobal);
		if ( NULL != hGlobal ) {
			ULONG size = ::SizeofResource(ATL::_AtlBaseModule.GetResourceInstance(), hResource);
			if ( size ) {
				BYTE *data = static_cast<BYTE *>(::LockResource(hGlobal));
				ATL::CComSafeArray<byte> saBuf(size);
				BYTE HUGEP *pSAMem;
				ATLVERIFY(S_OK == ::SafeArrayAccessData(saBuf.m_psa, (void HUGEP**)(&pSAMem)));
				::memcpy(pSAMem, data, size);
				::SafeArrayUnaccessData(saBuf.m_psa);
				rv = pFactory->CreateRasterFromMemory(saBuf.m_psa);
			}
		}
	}
	return rv;
}

} // namespace Util
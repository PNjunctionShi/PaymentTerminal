// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include <afxwinverapi.h>

// This file contains implementations of wrappers for methods used
// in MFC that are only available in later versions of Windows.

// When the minimum supported version of Windows is increased, the
// implementations of these methods just call the real Windows APIs.

#if _MFC_NTDDI_MIN >= NTDDI_VISTA
#pragma comment(lib, "propsys.lib")
#endif

#if _MFC_NTDDI_MIN >= NTDDI_WIN7
#pragma comment(lib, "dwmapi.lib")
#endif


HRESULT _AfxDwmExtendFrameIntoClientArea(HWND hWnd, __in const MARGINS *pMarInset)
{
#if _MFC_NTDDI_MIN >= NTDDI_VISTA
	return DwmExtendFrameIntoClientArea(hWnd, pMarInset);
#else
	// use DwmExtendFrameIntoClientArea if it is available (only on Vista+)...
	IFDYNAMICLOADCACHEDFUNCTIONFORMFC(L"dwmapi.dll", DwmExtendFrameIntoClientArea, pfDwmExtendFrameIntoClientArea)
	{
		return (*pfDwmExtendFrameIntoClientArea)(hWnd, pMarInset);
	}

	// ...otherwise return failure because there is no fallback.
	return E_FAIL;
#endif
}


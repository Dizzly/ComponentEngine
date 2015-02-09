#include "ReportError.h"

#ifdef WIN32
#include <Windows.h>
#endif

void ReportError(const std::string& errorMsg)
{
#ifdef WIN32
	MessageBoxA(0,errorMsg.c_str(),"Oh shi..", MB_ICONEXCLAMATION);
#endif
}
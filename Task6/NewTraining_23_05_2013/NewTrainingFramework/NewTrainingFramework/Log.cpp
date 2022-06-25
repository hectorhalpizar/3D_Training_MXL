#include "stdafx.h"
#include "Log.h"

#include <stdarg.h>

Log * Log::ms_pInstance = NULL;

void Log::printMessage(const char * TAG, const char * MSG,...)
{
#ifdef _DEBUG
	char str[2048];
	va_list arg_list;
	va_start(arg_list, MSG);
	vsprintf_s(str, MSG, arg_list);
	printf("%s: %s\n", TAG, str);
	va_end(arg_list);
#endif
}
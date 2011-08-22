
#include "windows.h"

HINSTANCE PDllInstance;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
  if (fdwReason == DLL_PROCESS_ATTACH)
    PDllInstance = hinstDLL;
  return TRUE;
}


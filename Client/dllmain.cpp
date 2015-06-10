#include <SAMP+/client/Client.h>
#include <SAMP+/client/CCmdlineParams.h>
#include <SAMP+/client/CHooks.h>

#pragma comment(lib, "d3dx9.lib")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			CLog::Initialize();
			CCmdlineParams::Process(GetCommandLine());
			CHooks::Apply();
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			CHooks::Remove();
			CLog::Finalize();
			break;
		}
	}
	return TRUE;
}

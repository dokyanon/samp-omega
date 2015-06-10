#pragma once

#include <DirectX/dinput.h>

class CDInput8Proxy : public IDirectInput8A
{
public:
	CDInput8Proxy(IDirectInput8A* device);
	~CDInput8Proxy();
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj);
    STDMETHOD_(ULONG,AddRef)(THIS);
    STDMETHOD_(ULONG,Release)(THIS);
    STDMETHOD(CreateDevice)(THIS_ REFGUID,LPDIRECTINPUTDEVICE8A*,LPUNKNOWN);
    STDMETHOD(EnumDevices)(THIS_ DWORD,LPDIENUMDEVICESCALLBACKA,LPVOID,DWORD);
    STDMETHOD(GetDeviceStatus)(THIS_ REFGUID);
    STDMETHOD(RunControlPanel)(THIS_ HWND,DWORD);
    STDMETHOD(Initialize)(THIS_ HINSTANCE,DWORD);
    STDMETHOD(FindDevice)(THIS_ REFGUID,LPCSTR,LPGUID);
    STDMETHOD(EnumDevicesBySemantics)(THIS_ LPCSTR,LPDIACTIONFORMATA,LPDIENUMDEVICESBYSEMANTICSCBA,LPVOID,DWORD);
    STDMETHOD(ConfigureDevices)(THIS_ LPDICONFIGUREDEVICESCALLBACK,LPDICONFIGUREDEVICESPARAMSA,DWORD,LPVOID);

private:
	IDirectInput8A* pDevice;
};

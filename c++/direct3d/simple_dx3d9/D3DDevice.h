#ifndef _D3D_MANAGER_H
#define _D3D_MANAGER_H
#include <d3d9.h>

class D3DDevice {
public:
	D3DDevice(HWND window, int width, int height);
	~D3DDevice();
	IDirect3DDevice9& GetDevice();
	void BeginScene();
	void PresentScene();
protected:
	IDirect3D9* context;
	IDirect3DDevice9* device;
	D3DPRESENT_PARAMETERS parameters;
};
#endif
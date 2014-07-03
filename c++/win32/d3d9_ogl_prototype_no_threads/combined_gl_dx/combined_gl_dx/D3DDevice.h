#ifndef _D3D_MANAGER_H
#define _D3D_MANAGER_H
#include <d3d9.h>

class Window;

class D3DDevice {
public:
	D3DDevice(Window *win);
	~D3DDevice();
	IDirect3DDevice9& GetDevice();
	void BeginScene();
	void PresentScene();
protected:
	IDirect3D9Ex *context;
	IDirect3DDevice9Ex *device;
	D3DPRESENT_PARAMETERS parameters;
};
#endif
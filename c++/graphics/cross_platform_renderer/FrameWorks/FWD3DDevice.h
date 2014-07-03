#ifndef _D3D_MANAGER_H
#define _D3D_MANAGER_H
#include <d3d9.h>
#include <d3dx9.h>

class FWWindow;

class FWD3DDevice {
public:
  FWD3DDevice(FWWindow *win);
  ~FWD3DDevice();
  IDirect3DDevice9Ex *GetDevice();
  void BeginScene();
  void PresentScene();
  void Resize(int width, int height);
protected:
  IDirect3D9Ex *context;
  IDirect3DDevice9Ex *device;
  D3DPRESENT_PARAMETERS parameters;
  FWWindow *win;
};
#endif
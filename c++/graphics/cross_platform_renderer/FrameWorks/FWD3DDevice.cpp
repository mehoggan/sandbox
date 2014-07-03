#include "FWD3DDevice.h"
#include "FWWindow.h"

FWD3DDevice::FWD3DDevice(FWWindow *win) :
    win(win)
{
  if ((Direct3DCreate9Ex(D3D_SDK_VERSION, &context)) != S_OK)
    throw(TEXT("D3DDevice Constructor: Failed to create a Direct3D Context!"));
  parameters.BackBufferWidth = win->getClientWidth(); 
  parameters.BackBufferHeight = win->getClientHeight();
  parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
  parameters.BackBufferCount = 1;
  parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
  parameters.MultiSampleQuality = 0;
  parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  parameters.hDeviceWindow = win->getHWND();
  parameters.Windowed = true;
  parameters.EnableAutoDepthStencil = true;
  parameters.AutoDepthStencilFormat = D3DFMT_D16;
  parameters.Flags = NULL;
  parameters.FullScreen_RefreshRateInHz = 0;
  parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
  if(FAILED(context->CreateDeviceEx(
    D3DADAPTER_DEFAULT, 
    D3DDEVTYPE_HAL, 
    win->getHWND(),
    D3DCREATE_MIXED_VERTEXPROCESSING, 
    &parameters, 
    NULL,
    &device))) 
  {
    LPCTSTR debugInfo = TEXT("D3DDevice Constructor: Failed to create device!\r\n");
	LPTSTR error = new TCHAR[256];
	wsprintf(error, TEXT("%s\r\n"), debugInfo);
	throw(error);
  }
}

FWD3DDevice::~FWD3DDevice() 
{
  if (device != NULL)
  {
    device->Release(); 
	device = NULL; 
  }
  if (context != NULL) 
  { 
    context->Release(); 
	context = NULL; 
  }
}

IDirect3DDevice9Ex *FWD3DDevice::GetDevice() 
{ 
  return device; 
}

void FWD3DDevice::BeginScene() 
{
	device->BeginScene();
}

void FWD3DDevice::PresentScene() 
{
  device->EndScene();
  device->Present(NULL, NULL, NULL, NULL);
}

void FWD3DDevice::Resize(int width, int height)
{
  D3DDISPLAYMODE d3dmodeTemp;
  device->GetDisplayMode(0, &d3dmodeTemp);
  WINDOWINFO wndInfo;
  parameters.BackBufferWidth = width;
  parameters.BackBufferHeight = height;
  parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
  parameters.BackBufferCount = 1;
  parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
  parameters.MultiSampleQuality = 0;
  parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  parameters.hDeviceWindow = win->getHWND();
  parameters.Windowed = true;
  parameters.EnableAutoDepthStencil = true;
  parameters.AutoDepthStencilFormat = D3DFMT_D16;
  parameters.Flags = NULL;
  parameters.FullScreen_RefreshRateInHz = 0;
  parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
  device->ResetEx(&parameters,NULL);

  D3DVIEWPORT9 vp;
  vp.X      = 0;
  vp.Y      = 0;
  vp.Width  = width;
  vp.Height = height;
  vp.MinZ   = 0.0f;
  vp.MaxZ   = 1.0f;
  device->SetViewport(&vp);
}
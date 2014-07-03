#include "D3DDevice.h"
#include "Window.h"

D3DDevice::D3DDevice(Window *win) 
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

D3DDevice::~D3DDevice() 
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

IDirect3DDevice9& D3DDevice::GetDevice() 
{ 
	return *device; 
}

void D3DDevice::BeginScene() 
{
	device->BeginScene();
}

void D3DDevice::PresentScene() 
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}
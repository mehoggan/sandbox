#include "D3DDevice.h"
D3DDevice::D3DDevice(HWND window, int width, int height) 
{
	context = Direct3DCreate9(D3D_SDK_VERSION);
	if (context == NULL) 
		throw(TEXT("D3DDevice Constructor: Failed to create a Direct3D Context!"));
	parameters.BackBufferWidth = width; parameters.BackBufferHeight = height;
	parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	parameters.BackBufferCount = 1;
	parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	parameters.MultiSampleQuality = 0;
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	parameters.hDeviceWindow = window;
	parameters.Windowed = true;
	parameters.EnableAutoDepthStencil = true;
	parameters.AutoDepthStencilFormat = D3DFMT_D16;
	parameters.Flags = NULL;
	parameters.FullScreen_RefreshRateInHz = 0;
	parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	HRESULT result = context->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
		D3DCREATE_MIXED_VERTEXPROCESSING, &parameters, &device);
	LPCTSTR debugInfo = TEXT("D3DDevice Constructor: Failed to create device!\r\n");
	if (result != D3D_OK) 
	{
		LPTSTR text;
	    if (result == D3DERR_INVALIDCALL) 
			text = TEXT("D3DERR_INVALIDCALL: Invalid Call or Parameter!");
	    else if (result == D3DERR_NOTAVAILABLE) 
			text = TEXT("D3DERR_NOTAVAILABLE: Parameter not supported!");
	    else if (result == D3DERR_OUTOFVIDEOMEMORY) 
			text = TEXT("D3DERR_OUTOFVIDEOMEMORY: Out of Video Memory!");
	    else {
		    text = new TCHAR[128];
		    wsprintf(text, TEXT("Unknown Error: %X"), result);
	    }
	    LPTSTR error = new TCHAR[256];
	    wsprintf(error, TEXT("%s\r\n%s"), debugInfo, text);
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
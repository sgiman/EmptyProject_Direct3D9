//***************************************************************************************
// File: EmptyProject.cpp
// Empty Project for DirectX (D3D9)
//
// Copyright (c) Microsoft Corporation. All rights reserved
//--------------------------------------------------------------------------------------
// Visual Studio 2010
// Microsoft DirectX SDK (June 2010)
//--------------------------------------------------------------------------------------
// Modified by sgiman, 2022, jul
//***************************************************************************************
#include "DXUT.h"
#include "resource.h"


//--------------------------------------------------------------------------------------
// Cбрасывает любые устройства D3D9, неприемлемые для приложения, возвращая false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Обычно требуется пропустить форматы обратного буфера, которые не поддерживают альфа-смешивание
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Перед созданием устройства изменить настройки устройства по мере необходимости
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//-----------------------------------------------------------------------------------------------
// Создайте любые ресурсы D3D9, которые будут работать после сброса устройства (D3DPOOL_MANAGED).
// и не привязаны к размеру заднего буфера
//-----------------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Создать любые ресурсы D3D9, которые не сохранятся после сброса устройства (D3DPOOL_DEFAULT)
// или которые привязаны к размеру заднего буфера
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//---------------------------------------------------------------------------------------------
// Обработка обновлений сцены. Это вызывается независимо от того, какой D3D API используется.
//---------------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Рендеринг сцены с помощью устройства D3D9
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Очистите цель рендеринга и zbuffer
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Рендеринг сцены
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Обработка сообщений в приложение
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


//--------------------------------------------------------------------------------------
// Освобождаем ресурсы D3D9, созданные в обратном вызове OnD3D9ResetDevice
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Освободить ресурсы D3D9, созданные в обратном вызове OnD3D9CreateDevice
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Инициализировать все и перейти в цикл рендеринга
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Включите проверку памяти во время выполнения для отладочных сборок.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Установите функции обратного вызова
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    //...................................................................
	// TODO: Выполните любую инициализацию на уровне приложения здесь ...
    //...................................................................

	// Инициализируем DXUT и создаем нужное окно Win32 и устройство Direct3D для приложения
	DXUTInit( true, true );						// Разобрать командную строку и показать msgboxes
    DXUTSetHotkeyHandling( true, true, true );	// Обрабатывать горячие клавиши по умолчанию
    DXUTSetCursorSettings( true, true ); 		// Показывать курсор и обрезать его в полноэкранном режиме
    DXUTCreateWindow( L"EmptyProject" );
    DXUTCreateDevice( true, 640, 480 );

	// Запустить цикл рендеринга
    DXUTMainLoop();

    // TODO: Выполните любую очистку на уровне приложения здесь ...

    return DXUTGetExitCode();
}

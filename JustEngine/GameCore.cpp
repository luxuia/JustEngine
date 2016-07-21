//
// Copyright (c) luxujia. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  luxuia@foxmail.com
//

#include "pch.h"
#include "GameCore.h"
#include "GraphicsCore.h"

namespace GameCore
{
	void InitializeApp( IGameApp& game )
	{
		Graphics::Init();

		game.Start();
	}

	void TerminateApp( IGameApp& game )
	{
		Graphics::Terminate();

		game.CleanUp();
	}

	bool UpdateApp( IGameApp& game )
	{
		game.Update(1.f/30.f);
		game.RenderScene();

		Graphics::Present();

		return !game.IsDone();
	}


	LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch (message)
		{
		case WM_PAINT:
		{
						 PAINTSTRUCT ps;
						 HDC hdc = BeginPaint( hWnd, &ps );
						 EndPaint( hWnd, &ps );
						 break;
		}

		case WM_SIZE:
			Graphics::Resize(wParam & 0xFFFFFF, lParam >> 16);
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
		}

		return 0;
	}

	HWND g_hWnd = nullptr;

	void RunApp( IGameApp& app, const wchar_t* className )
	{
		HINSTANCE hInst = GetModuleHandle( 0 );

		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_HREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = LoadIcon( hInst, IDI_APPLICATION );
		wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.hIconSm = LoadIcon( hInst, IDI_APPLICATION );
		wcex.lpszClassName = className;

		ASSERT( 0 != RegisterClassEx( &wcex ), "Unable to register a window" );

		RECT rect = { 0, 0, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT };
		AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );
		g_hWnd = CreateWindow( className, className, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInst, nullptr );

		ASSERT(g_hWnd != 0 );

		InitializeApp(app);

		ShowWindow(g_hWnd, SW_SHOWDEFAULT );

		do
		{
			MSG msg = {};
			while (PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ))
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			if (msg.message == WM_QUIT)
				break;
		} while (UpdateApp(app));	// Returns false to quit loop

		TerminateApp( app );
	}
}
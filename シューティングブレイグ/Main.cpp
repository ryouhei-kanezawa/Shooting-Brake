

#include "Dxlib.h"
#include "stdafx.h"
#include "main.h"
#include "mode.h"
#include "input.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[ MAX_LOADSTRING ];                  // タイトル バーのテキスト
WCHAR szWindowClass[ MAX_LOADSTRING ];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass( HINSTANCE hInstance );
BOOL                InitInstance( HINSTANCE, int );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK    About( HWND, UINT, WPARAM, LPARAM );


int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPWSTR    lpCmdLine,
					   _In_ int       nCmdShow ) {
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	ChangeWindowMode( TRUE );
	SetGraphMode( ScreenWidth, ScreenHeight, 32 );
	SetOutApplicationLogValidFlag( FALSE );

	SetUseCharCodeFormat( DX_CHARCODEFORMAT_UTF8 );
	if ( DxLib_Init( ) == 1 ) { return -1; }

	SetDrawScreen( DX_SCREEN_BACK );

	int ext;
	while ( ProcessMessage( ) == 0 ) {
		ScreenFlip( );
		ClearDrawScreen( );
		inputPeripheralUpdate();

		ext = modeCtrl(0);
		
		if (ext) { break; }
	}

	DxLib_End( );
	return (int)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
	{
	}
	break;
	case WM_PAINT:
	{
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
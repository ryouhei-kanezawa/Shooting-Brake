

#include "Dxlib.h"
#include "stdafx.h"
#include "main.h"
#include "mode.h"
#include "input.h"

#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;                                // ���݂̃C���^�[�t�F�C�X
WCHAR szTitle[ MAX_LOADSTRING ];                  // �^�C�g�� �o�[�̃e�L�X�g
WCHAR szWindowClass[ MAX_LOADSTRING ];            // ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
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
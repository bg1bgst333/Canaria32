// ヘッダのインクルード
// 独自のヘッダ
#include "MainApplication.h"	// CMainApplication

// インスタンス初期化関数InitInstance.
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd){

	// ウィンドウクラスの登録.
	CWindow::RegisterClass(hInstance, _T("CWindow"));	// CWindow::RegisterClassでウィンドウクラス"CWindow"を登録.

	// ウィンドウの作成.
	if (!m_mainWnd.Create(_T("CWindow"), _T("Canaria"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance)){	// m_mainWnd.Createでウィンドウ作成し, 失敗した場合.

		// エラー処理
		return FALSE;	// returnでFALSEを返して異常終了.

	}

	// ウィンドウの表示.
	m_mainWnd.ShowWindow(SW_SHOW);	// m_mainWnd.ShowWindowで表示.

	// TRUEを返す.
	return TRUE;	// returnでTRUEを返す.

}
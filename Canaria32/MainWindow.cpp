// ヘッダのインクルード
// 既定のヘッダ
#include <locale.h>	// ロケール
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// メンバの初期化.
	m_pPicture = NULL;	// m_pPictureをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理.
	if (m_pPicture != NULL){	// m_pPictureがNULLでない時.
		delete m_pPicture;	// deleteでm_pPictureを破棄.
		m_pPicture = NULL;	// m_pPictureにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはIDR_MENU1を使う.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューlpszMenuNameを使う.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), lpszMenuName);	// メニュー名を指定する.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// メニューバーの作成.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBarオブジェクトm_pMenuBarを作成.

	// メニューのロード.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenuでIDR_MENU1をロード.

	// メニューのセット.
	m_pMenuBar->SetMenu(hwnd);	// SetMenuでhwndにメニューをセット.

	// ピクチャーの生成.
	m_pPicture = new CPicture();	// CPictureオブジェクトを生成して, m_pPictureに格納.
	m_pPicture->Create(_T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SS_REALSIZECONTROL, 0, 0, 0, 0, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pPicture->Createでピクチャーコントロールを作成.(SS_REALSIZECONTROLはコントロールの大きさに合わせて縮小され, SS_REALSIZEIMAGEは画像サイズに合わせてコントロールが拡大する.)

	// スクロールバー設定.
	// 水平方向の設定.
#if 0
	m_scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズはsizeof(SCROLLINFO).
	m_scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// 設定する項目のフラグはページとレンジ.
	m_scrollInfo.nPage = 0;	// 最初は0.
	m_scrollInfo.nMin = 0;	// 最小値は0.
	m_scrollInfo.nMax = 0;	// 最初は0.
	SetScrollInfo(m_hPicture, SB_HORZ, &m_scrollInfo, FALSE);	// SetScrollInfoでm_scrollInfoをセット.
	// 垂直方向の設定.
	m_scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズはsizeof(SCROLLINFO).
	m_scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// 設定する項目のフラグはページとレンジ.
	m_scrollInfo.nPage = 0;	// 最初は0.
	m_scrollInfo.nMin = 0;	// 最小値は0.
	m_scrollInfo.nMax = 0;	// 最初は0.
	SetScrollInfo(m_hPicture, SB_VERT, &m_scrollInfo, FALSE);	// SetScrollInfoでm_scrollInfoをセット.
#endif

	// メニューハンドラの追加.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandlerでID_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandlerでID_FILE_SAVE_ASに対するハンドラCMainWindow::OnFileSaveAsを登録.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandlerでID_FILE_OPENのハンドラを削除.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandlerでID_FILE_SAVE_ASのハンドラを削除.

	// CWindowのOnDestroyを呼ぶ.
	CWindow::OnDestroy();	// CWindow::OnDestroyを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// メンバにセット.
	MoveWindow(m_pPicture->m_hWnd, 0, 0, cx, cy, TRUE);	// MoveWindowでm_pPicture->m_hWndのサイズをクライアント領域と同じにする.
	
	// 自分のサイズを計測.
	RECT rc = {0};
	GetWindowRect(m_hWnd, &rc);
	m_iWidth = rc.right - rc.left;
	m_iHeight = rc.bottom - rc.top;

}

// "開く"を選択された時のハンドラ.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "開く"ファイルの選択.
	CFileDialog selDlg(NULL, _T("bmp"), _T("ビットマップ画像(*.bmp)|*.bmp|すべてのファイル(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialogで"開く"ファイルダイアログを表示.

		// インスタンスハンドルの取得.
		HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWLP_HINSTANCE);	// GetWindowLongでインスタンスハンドルを取得.
		// ロード.
		if (m_pPicture->LoadImage(hInstance, selDlg.m_tstrPath.c_str())){	// m_pPicture->LoadImageでロード.
			// セット.
			m_pPicture->SetImage();	// m_pPicture->SetImageでセット.
		}

	}

	// 処理していないので-1.
	return -1;	// returnで-1を返す.

}

// "名前を付けて保存"を選択された時のハンドラ.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "名前を付けて保存"ファイルの選択.
	CFileDialog selDlg(NULL, _T("bmp"), _T("ビットマップ画像(*.bmp)|*.bmp|すべてのファイル(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログを表示.
		
		// セーブ.
		m_pPicture->SaveImage(selDlg.m_tstrPath.c_str());	// m_pPicture->SaveImageでセーブ.
		
	}

	// 処理していないので-1.
	return -1;	// returnで-1を返す.

}
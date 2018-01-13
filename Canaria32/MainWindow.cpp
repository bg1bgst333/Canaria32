// ヘッダのインクルード
// 既定のヘッダ
#include <locale.h>	// ロケール
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// リソース

// static変数の宣言
static CMainWindow *pMainWnd = NULL;	// staticでCMainWindowオブジェクトポインタpMainWndをNULLで初期化.

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CWindow(){

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

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

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

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// 終了メッセージの送信.
	PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

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

// コマンドが発生した時.
BOOL  CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// コマンドの処理.
	switch (LOWORD(wParam)){	// LOWORD(wParam)でリソースIDがわかるので, その値ごとに処理を振り分ける.

		// "開く(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPENブロック
			{

				// "開く"ファイルの選択.
				// 構造体・配列の初期化.
				OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.
				TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
				// パラメータのセット.
				ofn.lStructSize = sizeof(OPENFILENAME);	// sizeofでOPENFILENAME構造体のサイズをセット.
				ofn.hwndOwner = m_hWnd;	// m_hWndをセット.
				ofn.lpstrFilter = _T("ビットマップ画像(*.bmp)\0*.bmp\0すべてのファイル(*.*)\0*.*\0\0");	// ビットマップ画像とすべてのファイルのフィルタをセット.
				ofn.lpstrFile = tszPath;	// tszPathをセット.
				ofn.nMaxFile = _MAX_PATH;	// _MAX_PATHをセット.
				ofn.Flags = OFN_FILEMUSTEXIST;	// ファイルが存在しないと抜けられない.
				// "開く"ファイルダイアログの表示.
				BOOL bRet = GetOpenFileName(&ofn);	// GetOpenFileNameでファイルダイアログを表示し, 選択されたファイル名を取得する.(戻り値をbRetに格納.)
				if (bRet){	// 正常に選択された.

					// インスタンスハンドルの取得.
					HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWLP_HINSTANCE);	// GetWindowLongでインスタンスハンドルを取得.
					// ロード.
					if (m_pPicture->LoadImage(hInstance, tszPath)){	// m_pPicture->LoadImageでロード.
						// セット.
						m_pPicture->SetImage();	// m_pPicture->SetImageでセット.
					}

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// "名前を付けて保存(&A)..."
		case ID_FILE_SAVE_AS:

			// ID_FILE_SAVE_ASブロック
			{

				// "名前を付けて保存"するファイルの選択.
				// 構造体・配列の初期化.
				OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.
				TCHAR tszPath[_MAX_PATH] =  {0};	// ファイルパスtszPathを{0}で初期化.
				// パラメータのセット.
				ofn.lStructSize = sizeof(OPENFILENAME);	// sizeofでOPENFILENAME構造体のサイズをセット.
				ofn.hwndOwner = m_hWnd;	// m_hWndをセット.
				ofn.lpstrFilter = _T("ビットマップ画像(*.bmp)\0*.bmp\0すべてのファイル(*.*)\0*.*\0\0");	// ビットマップ画像とすべてのファイルのフィルタをセット.
				ofn.lpstrFile = tszPath;	// tszPathをセット.
				ofn.nMaxFile = _MAX_PATH;	// _MAX_PATHをセット.
				ofn.Flags = OFN_OVERWRITEPROMPT;	// 既にファイルがある時, 上書きするかの確認を表示.
				// "名前を付けて保存"ファイルダイアログを表示.
				BOOL bRet = GetSaveFileName(&ofn);	// GetSaveFileNameでファイルダイアログを表示し, 選択されたファイル名を取得する.(戻り値をbRetに格納.)
				if (bRet){	// 正常に選択された.
					
					// セーブ.
					m_pPicture->SaveImage(tszPath);	// m_pPicture->SaveImageでセーブ.
					
				}

			}
		
			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// それ以外.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// TRUE.
	return TRUE;	// TRUEを返す.

}
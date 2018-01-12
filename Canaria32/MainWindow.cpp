// ヘッダのインクルード
// 既定のヘッダ
#include <locale.h>	// ロケール
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// リソース

// staticメンバ変数の宣言
WNDPROC CMainWindow::m_lpfnWndProc = NULL;	// NULLで初期化.

// static変数の宣言
static CMainWindow *pMainWnd = NULL;	// staticでCMainWindowオブジェクトポインタpMainWndをNULLで初期化.

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// メンバの初期化.
	m_hPicture = NULL;	// m_hPictureをNULLで初期化.
	m_iWidth = 0;	// m_iWidthを0で初期化.
	m_iHeight = 0;	// m_iHeightを0で初期化.
	m_hBitmap = NULL;	// m_hBitmapをNULLで初期化.
	m_hMemDC = NULL;	// m_hMemDCをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理.
	if (m_hPicture != NULL){	// m_hPictureがNULLでない時.
		DestroyWindow(m_hPicture);	// DestroyWindowでm_hPictureを破棄.
		m_hPicture = NULL;	// m_hPictureにNULLをセット.
	}
	m_iWidth = 0;	// m_iWidthを0で初期化.
	m_iHeight = 0;	// m_iHeightを0で初期化.
	if (m_hBitmap != NULL){	// m_hBitmapがNULLでない時.
		DeleteObject(m_hBitmap);	// DeleteObjectでm_hBitmapを破棄.
		m_hBitmap = NULL;	// m_hBitmapにNULLをセット.
	}
	if (m_hMemDC != NULL){	// m_hMemDCがNULLでない時.
		DeleteDC(m_hMemDC);	// DeleteDCでm_hMemDCを破棄.
		m_hMemDC = NULL;	// m_hMemDCにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはIDR_MENU1を使う.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClassで登録.

}

// スタティックウィンドウプロシージャPictureProc.(ピクチャーコントロールのプロシージャ差し替え先.)
LRESULT CALLBACK CMainWindow::PictureProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// static変数の宣言.
	static SCROLLINFO scrollInfo = {0};	// スクロール情報構造体scrollInfoを{0}で初期化.
	//static HDC hMemDC = NULL;	// メモリデバイスコンテキストハンドルhMemDCをNULLで初期化.
	//static HBITMAP hBitmap = NULL;	// ビットマップハンドルhBitmapをNULLで初期化.
	//static BITMAP bitmap = {0};	// BITMAP構造体オブジェクトbitmapを{0}で初期化.
	//static CMainWindow *pMainWnd = NULL;	// CMainWindowオブジェクトポインタpMainWndをNULLで初期化.
	static int iHScrollPos = 0;	// iHScrollPosを0で初期化.
	static int iVScrollPos = 0;	// iVScrollPosを0で初期化.

	// ウィンドウメッセージ処理
	switch (uMsg) {

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{
				// 変数の宣言
				LPCREATESTRUCT lpCS;	// CreateStruct構造体ポインタlpCS.

				// lpCSの取得.
				lpCS = (LPCREATESTRUCT)lParam;	// lParamをLPCREATESTRUCTにキャストして, lpCSに格納.

				// pMainWndにポインタを格納.
				pMainWnd = (CMainWindow *)lpCS->lpCreateParams;	// lpCS->lpCreateParamsを(CMainWindow *)にキャストしてpMainWndに格納.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// メモリデバイスコンテキストの破棄.
				if (pMainWnd->m_hMemDC != NULL){	// pMainWnd->m_hMemDCがNULLでなければ.
					// 削除.
					DeleteDC(pMainWnd->m_hMemDC);	// DeleteDCでpMainWnd->m_hMemDCを解放.
					pMainWnd->m_hMemDC = NULL;	// pMainWnd->m_hMemDCにNULLをセット.
				}
				// ビットマップが残っていたら削除.
				if (pMainWnd->m_hBitmap != NULL){	//pMainWnd->m_hBitmapがNULLでない.
					// 削除.
					DeleteObject(pMainWnd->m_hBitmap);	// DeleteObjectでpMainWnd->m_hBitmapを削除.
					pMainWnd->m_hBitmap = NULL;	// pMainWnd->m_hBitmapにNULLをセット.
				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 画面の描画を要求された時.
		case WM_PAINT:

			// WM_PAINTブロック
			{

				// 変数の初期化.
				HDC hDC = NULL;	// hDCをNULLで初期化.
				PAINTSTRUCT ps = {0};	// psを{0}で初期化.
				HBITMAP hOld = NULL;	// hOldをNULLで初期化.
				int iDrawWidth;	// 実際の描画幅.
				int iDrawHeight;	// 実際の描画高さ.

				// 描画開始.
				hDC = BeginPaint(hwnd, &ps);	// BeginPaintで描画開始.

				// ビットマップの選択.
				hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObjectでhMemDCにpMainWnd->m_hBitmapを選択.
				
				// ビット転送.
				iDrawWidth = pMainWnd->m_iWidth - SCROLLBAR_THICKNESS;	// 描画幅 = ピクチャーコントロール幅 - スクロールバー幅.
				iDrawHeight = pMainWnd->m_iHeight - SCROLLBAR_THICKNESS;	// 描画高さ = ピクチャーコントロール高さ - スクロールバー高さ.
				BitBlt(hDC, 0, 0, iDrawWidth, iDrawHeight, pMainWnd->m_hMemDC, iHScrollPos, iVScrollPos, SRCCOPY);	// BitBltでhMemDCをhDCに転送.

				// 古いビットマップを再選択して戻す.
				SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObjectでhOldを選択.

				// スクロールバー設定.
				// 水平方向.
				ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでscrollInfoをクリア.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
				scrollInfo.nPage = iDrawWidth;	// 描画幅
				scrollInfo.nMin = 0;	// 最小値
				scrollInfo.nMax = pMainWnd->m_Bitmap.bmWidth;	//最大値
				SetScrollInfo(hwnd, SB_HORZ, &scrollInfo, FALSE);	// SetScrollInfoでセット.
				// 垂直方向.
				ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでscrollInfoをクリア.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
				scrollInfo.nPage = iDrawHeight;	// 描画高さ
				scrollInfo.nMin = 0;	// 最小値
				scrollInfo.nMax =  pMainWnd->m_Bitmap.bmHeight;	//最大値
				SetScrollInfo(hwnd, SB_VERT, &scrollInfo, FALSE);	// SetScrollInfoでセット.

				// 描画終了.
				EndPaint(hwnd, &ps);	// EndPaintで描画終了.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// これらのメッセージはDefWindowProcに投げないと, スクロールバーが認識せず動作しない.
		case WM_NCHITTEST:
		case WM_NCLBUTTONDOWN:
		case WM_NCLBUTTONUP:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProcの値を返す.

		// 水平方向のスクロールが発生した時.
		case WM_HSCROLL:

			// WM_HSCROLLブロック
			{

				// スクロール情報取得.
				UINT nSBCode = LOWORD(wParam);	// LOWORD(wParam)でスクロール動作の種類を取得.
				UINT nPos = HIWORD(wParam);	// HIWORD(wParam)でスクロールバーの位置を取得.
				scrollInfo.fMask = SIF_POS;	// 位置のみ変更.
				GetScrollInfo(hwnd, SB_HORZ, &scrollInfo);	// GetScrollInfoで位置情報の取得.

				// スクロールバー処理.
				switch (nSBCode){	// nSBCodeの値で処理を振り分ける.

					// 一番左
					case SB_LEFT:

						// SB_LEFTブロック
						{

							// 位置を最小値に.
							scrollInfo.nPos = scrollInfo.nMin;	// nMinをセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 一番右
					case SB_RIGHT:

						// SB_RIGHTブロック
						{

							// 位置を最大値に.
							scrollInfo.nPos = scrollInfo.nMax;	// nMaxをセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1列左
					case SB_LINELEFT:

						// SB_LINELEFTブロック
						{

							// nPosが0でなければデクリメント.
							if (scrollInfo.nPos > 0){
								scrollInfo.nPos--;	// nPosをデクリメント.
							}

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1列右
					case SB_LINERIGHT:

						// SB_LINERIGHTブロック
						{

							// nPosが最大値-1でなければインクリメント.
							if (scrollInfo.nPos < scrollInfo.nMax - 1){
								scrollInfo.nPos++;	// nPosをインクリメント.
							}

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1ページ左
					case SB_PAGELEFT:

						// SB_PAGELEFTブロック
						{

							// nPage分減らす.
							scrollInfo.nPos -= scrollInfo.nPage;	// nPosからnPage分引く.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1ページ右
					case SB_PAGERIGHT:

						// SB_PAGERIGHTブロック
						{

							// nPage分増やす.
							scrollInfo.nPos += scrollInfo.nPage;	// nPosからnPage分足す.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// つまみをドラッグ中.
					case SB_THUMBTRACK:

						// SB_THUMBTRACKブロック
						{

							// 引数のnPosをセット.
							scrollInfo.nPos = nPos;	// 引数のnPosをscrollInfo.nPosにセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// つまみをドラッグ後.
					case SB_THUMBPOSITION:

						// SB_THUMBPOSITIONブロック
						{

							// 引数のnPosをセット.
							scrollInfo.nPos = nPos;	// 引数のnPosをscrollInfo.nPosにセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// それ以外.
					default:

						// 抜ける.
						break;	// breakで抜ける.

				};

				// スクロール情報設定.
				SetScrollInfo(hwnd, SB_HORZ, &scrollInfo, TRUE);	// SetScrollInfoでスクロール情報をセット.
				// 水平位置のセット.
				iHScrollPos = scrollInfo.nPos;	// iHScrollPosにscrollInfo.nPosをセット.
				// 無効領域を作成して画面の更新.
				InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRectで更新.
				// 元々のピクチャーコントロールのウィンドウプロシージャに任せる.
				//return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProcでlpfnWndProcに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 垂直方向スクロールバーのイベントが発生した時.
		case WM_VSCROLL:

			// WM_VSCROLLブロック
			{

				// スクロール情報取得.
				UINT nSBCode = LOWORD(wParam);	// LOWORD(wParam)でスクロール動作の種類を取得.
				UINT nPos = HIWORD(wParam);	// HIWORD(wParam)でスクロールバーの位置を取得.
				scrollInfo.fMask = SIF_POS;	// 位置のみ変更.
				GetScrollInfo(hwnd, SB_VERT, &scrollInfo);	// GetScrollInfoで位置情報の取得.

				// スクロールバー処理.
				switch (nSBCode){	// nSBCodeの値で処理を振り分ける.

					// 一番上
					case SB_TOP:

						// SB_TOPブロック
						{

							// 位置を最小値に.
							scrollInfo.nPos = scrollInfo.nMin;	// nMinをセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 一番下
					case SB_BOTTOM:

						// SB_BOTTOMブロック
						{

							// 位置を最大値に.
							scrollInfo.nPos = scrollInfo.nMax;	// nMaxをセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1列上
					case SB_LINEUP:

						// SB_LINEUPブロック
						{

							// nPosが0でなければデクリメント.
							if (scrollInfo.nPos > 0){
								scrollInfo.nPos--;	// nPosをデクリメント.
							}

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1列下
					case SB_LINEDOWN:

						// SB_LINEDOWNブロック
						{

							// nPosが最大値-1でなければインクリメント.
							if (scrollInfo.nPos < scrollInfo.nMax - 1){
								scrollInfo.nPos++;	// nPosをインクリメント.
							}

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1ページ上
					case SB_PAGEUP:

						// SB_PAGEUPブロック
						{

							// nPage分減らす.
							scrollInfo.nPos -= scrollInfo.nPage;	// nPosからnPage分引く.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// 1ページ下
					case SB_PAGEDOWN:

						// SB_PAGEDOWNブロック
						{

							// nPage分増やす.
							scrollInfo.nPos += scrollInfo.nPage;	// nPosからnPage分足す.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// つまみをドラッグ中.
					case SB_THUMBTRACK:

						// SB_THUMBTRACKブロック
						{

							// 引数のnPosをセット.
							scrollInfo.nPos = nPos;	// 引数のnPosをscrollInfo.nPosにセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// つまみをドラッグ後.
					case SB_THUMBPOSITION:

						// SB_THUMBPOSITIONブロック
						{

							// 引数のnPosをセット.
							scrollInfo.nPos = nPos;	// 引数のnPosをscrollInfo.nPosにセット.

						}

						// 抜ける.
						break;	// breakで抜ける.

					// それ以外.
					default:

						// 抜ける.
						break;	// breakで抜ける.

				};

				// スクロール情報設定.
				SetScrollInfo(hwnd, SB_VERT, &scrollInfo, TRUE);	// SetScrollInfoでスクロール情報をセット.
				// 垂直位置のセット.
				iVScrollPos = scrollInfo.nPos;	// iVScrollPosにscrollInfo.nPosをセット.
				// 無効領域を作成して画面の更新.
				InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRectで更新.
				// 元々のピクチャーコントロールのウィンドウプロシージャに任せる.
				//return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProcでlpfnWndProcに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// マウスが移動している時.
		case WM_MOUSEMOVE:

			// WM_MOUSEMOVEブロック
			{

				// 座標の取得.
				int x = LOWORD(lParam);	// LOWORD(lParam)がx座標.
				int y = HIWORD(lParam);	// HIWORD(lParam)がy座標.

				// マウスダウンフラグが立っている時.
				if (wParam == MK_LBUTTON){	// 左ボタンが押されている時.

					// ビットマップの選択.
					HBITMAP hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObjectでpMainWnd->m_hBitmapを選択.

					// 押された場所に黒い点をセット.
					SetPixel(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixelで黒い点をセット.

					// 前回の場所から押された場所までの直線を描く.
					LineTo(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos);	// LineToで押された場所までの直線を描く.

					// 押された場所に始点を移動.
					MoveToEx(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, NULL);	// MoveToExで始点を移動.

					// 古いビットマップを再選択.
					SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObjectでhOldを選択.

					// 画面更新.
					InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRectで画面更新.

				}
				else{	// マウスダウンフラグが立っていない時.

					// マウスの移動場所に始点を移動.
					MoveToEx(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, NULL);	// MoveToExで始点を移動.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// マウスの左ボタンが押された時.
		case WM_LBUTTONDOWN:

			// WM_LBUTTONDOWNブロック
			{

				// 座標の取得.
				int x = LOWORD(lParam);	// LOWORD(lParam)がx座標.	
				int y = HIWORD(lParam);	// HIWORD(lParam)がy座標.

				// マウスダウンフラグが立っている時.
				if (wParam == MK_LBUTTON){	// 左ボタンが押されている時.

					// ビットマップの選択.
					HBITMAP hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObjectでpMainWnd->m_hBitmapを選択.

					// 押された場所に黒い点をセット.
					SetPixel(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixelで黒い点をセット.

					// 古いビットマップを再選択.
					SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObjectでhOldを選択.

					// 画面更新.
					InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRectで画面更新.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// マウスの左ボタンが離された時.
		case WM_LBUTTONUP:

			// WM_LBUTTONUPブロック
			{

				// 座標の取得.
				int x = LOWORD(lParam);	// LOWORD(lParam)がx座標.
				int y = HIWORD(lParam);	// HIWORD(lParam)がy座標.

				// マウスダウンフラグが立っている時.
				if (wParam == MK_LBUTTON){	// 左ボタンが押されている時.

					// ビットマップの選択.
					HBITMAP hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObjectでpMainWnd->m_hBitmapを選択.

					// 押された場所に黒い点をセット.
					SetPixel(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixelで黒い点をセット.

					// 古いビットマップを再選択.
					SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObjectでhOldを選択.

					// 画面更新.
					InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRectで画面更新.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 上記以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	};

	// 既定のプロシージャに任せる.
	return CallWindowProc(m_lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProcでこのメッセージをm_mapBaseWindowProcMap[tszClassName]に任せる.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 自身のポインタを保存.
	pMainWnd = this;	// pMainWndにthisをセット.

	// ピクチャーコントロールの作成
	m_hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SS_BITMAP | SS_REALSIZECONTROL, 0, 0, m_iWidth, m_iHeight, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance, NULL);	// CreateWindowでピクチャーコントロールm_hPictureを作成.(ウィンドウクラス名は"Static".SS_REALSIZECONTROLなのでコントロールサイズに合わせて画像が拡大縮小される.)

	// ピクチャーコントロール既定のウィンドウプロシージャを取得し, PictureProcに差し替える.
	m_lpfnWndProc = (WNDPROC)GetWindowLong(m_hPicture, GWL_WNDPROC);	// GetWindowLongでプロシージャm_lpfnWndProcを取得.
	SetWindowLong(m_hPicture, GWL_WNDPROC, (LONG)PictureProc);	// SetWindowLongでPictureProcをセット.

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

	// ピクチャーのサイズ変更.
	m_iWidth = cx;
	m_iHeight = cy;
	MoveWindow(m_hPicture, 0, 0, cx, cy, TRUE);	// MoveWindowでm_hPictureのサイズをクライアント領域と同じにする.

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

					// ウィンドウサイズのセット.
					RECT rc = {0};
					GetClientRect(pMainWnd->m_hWnd, &rc);
					pMainWnd->m_iWidth = rc.right;
					pMainWnd->m_iHeight = rc.bottom;

					// ビットマップが既にロード済みの場合.
					if (m_hBitmap != NULL){	// m_hBitmapがNULLでない.
						// 一旦削除.
						DeleteObject(m_hBitmap);	// DeleteObjectでm_hBitmapを削除.
						m_hBitmap = NULL;	// m_hBitmapにNULLをセット.
					}

					// ビットマップのロード.
					HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);	// GetWindowLongでアプリケーションインスタンスハンドルhInstanceを取得.
					m_hBitmap = (HBITMAP)LoadImage(hInstance, tszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// LoadImageでビットマップをロード.

					// 画像の幅と高さを取得.
					ZeroMemory(&m_Bitmap, sizeof(BITMAP));	// ZeroMemoryでm_Bitmapを0で初期化.
					GetObject(m_hBitmap, sizeof(BITMAP), &m_Bitmap);	// GetObjectでm_hBitmapからBITMAP構造体を取得.
					
					// デバイスコンテキストハンドルの初期化.
					HDC hDC = NULL;	// hDCをNULLで初期化.

					// デバイスコンテキストハンドルの取得.
					hDC = GetDC(m_hPicture);	// GetDCでm_hPictureのデバイスコンテキストhDCを取得.

					// いったんメモリデバイスコンテキストの破棄.
					if (m_hMemDC != NULL){	// m_hMemDCがNULLでなければ.
						DeleteDC(m_hMemDC);	// DeleteDCでm_hMemDCを解放.
						m_hMemDC = NULL;	// m_hMemDCにNULLをセット.
					}

					// メモリデバイスコンテキストの作成.
					m_hMemDC = CreateCompatibleDC(hDC);	// CreateCompatibleDCでhDCからm_hMemDCを作成.

					// ビットマップの表示.
					SendMessage(m_hPicture, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);	// SendMessageでSTM_SETIMAGEを送ることでm_hBitmapを表示.

					// デバイスコンテキストの解放.
					ReleaseDC(m_hPicture, hDC);	// ReleaseDCでhDCを解放.

					// 無効領域を作成して画面の更新.
					InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

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
					
					// 変数の初期化.
					BITMAPINFO bi = {0};	// BITMAPINFO構造体変数biを{0}で初期化.
					LPBYTE lpBitsPixel = NULL;	// LPBYTE型(BYTE型ポインタ)のlpBitsPixelをNULLで初期化.
					BITMAPFILEHEADER bfh = {0};	// BITMAPFILEHEADER構造体bfhを{0}で初期化.
					HDC hDC = NULL;	// hDCをNULLで初期化.
					FILE *fp = NULL;	// ファイルポインタfpをNULLで初期化.

					// ビットマップ情報のセット.
					bi.bmiHeader.biBitCount = 24;	// ひとまず24bitビットマップのみ対応.
					bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// BITMAPINFOHEADERのサイズを指定しておく.
					bi.bmiHeader.biWidth = m_Bitmap.bmWidth;	// 画像幅m_Bitmap.bmWidthをセット.
					bi.bmiHeader.biHeight = m_Bitmap.bmHeight;	// 画像高さm_Bitmap.bmHeightをセット.
					bi.bmiHeader.biPlanes = 1;	// 1をセット.
					bi.bmiHeader.biCompression = BI_RGB;	// RGB.

					// DDBからDIBのピクセル列を取得.
					hDC = GetDC(m_hPicture);	// GetDCでm_hPictureのデバイスコンテキストhDCを取得.
					GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, NULL, &bi, DIB_RGB_COLORS);	// GetDIBitsでピクセル列のサイズ(bi.bmiHeader.biSizeImage)を取得.
					lpBitsPixel = new BYTE[bi.bmiHeader.biSizeImage];	// ピクセル列用のメモリ確保.
					GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, lpBitsPixel, &bi, DIB_RGB_COLORS);	// GetDIBitsでピクセル列を取得.
					ReleaseDC(m_hPicture, hDC);	// hDCをリリース.

					// ビットマップファイル情報のセット.(24bitビットマップの場合.)
					bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	// ピクセル列以外のサイズ.(つまりヘッダのサイズ.)
					bfh.bfSize = bfh.bfOffBits + bi.bmiHeader.biSizeImage;	// 全体のサイズはヘッダ + ピクセル列.
					bfh.bfType = 0x4d42;	// 0x4d42("BM")はビットマップであるという意味.
					bfh.bfReserved1 = 0;	// ここは0をセット.
					bfh.bfReserved2 = 0;	// ここは0をセット.

					// ファイルの書き込み.
					// 日本語ロケールのセット.
					setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.
					// ファイル名をマルチバイトに変換.
					size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombsで長さfilename_lenを求める.(filename_lenにNULL文字は含まれない.)
					char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// mallocで動的配列を確保し, アドレスをpathに格納.
					wcstombs(path, tszPath, _MAX_PATH);	// wcstombsでTCHARからマルチバイトへ変換.
					// ファイルを開く.
					fp = fopen(path, "wb");	// バイナリモード("wb")で開く.
					if (fp != NULL){	// fpがNULLでない時.
						fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);	// fwriteでbfhを書き込む.
						fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);	// fwriteでbiを書き込む.
						fwrite(lpBitsPixel, sizeof(BYTE), bi.bmiHeader.biSizeImage, fp);	// fwriteでlpBitsPixelを書き込む.
						fclose(fp);	// fcloseでfpを閉じる.
					}
					// メモリの解放.
					free(path);	// freeでpathを解放.
					delete[] lpBitsPixel;	// delete[]でlpBitsPixelを解放.

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
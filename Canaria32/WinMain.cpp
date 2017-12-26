// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>		// C標準入出力
#include <stdlib.h>		// C標準ユーティリティ
#include <locale.h>		// ロケール
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
// 独自のヘッダ
#include "resource.h"	// リソース

// マクロの定義
#define SCROLLBAR_THICKNESS 16	// とりあえずスクロールバーの厚さはマクロで16としておく.

// 関数のプロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc

// _tWinMain関数の定義
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd){

	// 変数・構造体の宣言
	HWND hWnd;		// HWND型ウィンドウハンドルhWnd
	MSG msg;		// MSG型メッセージ構造体msg
	WNDCLASS wc;	// WNDCLASS型ウィンドウクラス構造体wc

	// ウィンドウクラス構造体wcにパラメータをセット.
	wc.lpszClassName = _T("Canaria");	// ウィンドウクラス名はとりあえず"Canaria"とする.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// スタイルはとりあえずCS_HREDRAW | CS_VREDRAWにする.
	wc.lpfnWndProc = WindowProc;	// ウィンドウプロシージャには下で定義するWindowProcを指定する.
	wc.hInstance = hInstance;	// アプリケーションインスタンスハンドルは引数のhInstanceを使う.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// LoadIconでアプリケーション既定のアイコンをロード.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// LoadCursorでアプリケーション既定のカーソルをロード.
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	// GetStockObjectでライトグレーブラシを背景色とする.
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// MAKEINTRESOURCEにメニューのリソースID(IDR_MENU1)を指定し, wc.lpszMenuNameに格納.
	wc.cbClsExtra = 0;	// とりあえず0を指定.
	wc.cbWndExtra = 0;	// とりあえず0を指定.

	// ウィンドウクラスの登録
	if (!RegisterClass(&wc)){	// RegisterClassでウィンドウクラスを登録する.

		// 戻り値が0なら登録失敗なのでエラー処理.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-1)"), _T("Canaria"), MB_OK | MB_ICONHAND);	// MessageBoxで"予期せぬエラーが発生しました!(-1)"と表示.
		return -1;	// returnで-1を返して異常終了.

	}

	// ウィンドウの作成
	hWnd = CreateWindow(wc.lpszClassName, _T("Canaria"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);	// CreateWindowでウィンドウクラス名が"Canaria"なウィンドウ"Canaria"を作成.
	if (hWnd == NULL){	// hWndがNULLならウィンドウ作成失敗.

		// エラー処理
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-2)"), _T("Canaria"), MB_OK | MB_ICONHAND);	// MessageBoxで"予期せぬエラーが発生しました!(-2)"と表示.
		return -2;	// returnで-2を返して異常終了.

	}

	// ウィンドウの表示
	ShowWindow(hWnd, SW_SHOW);	// ShowWindowでウィンドウを表示.

	// メッセージループの処理
	while (GetMessage(&msg, NULL, 0, 0) > 0){	// GetMessageでウィンドウメッセージを取得し, msgに格納.(0以下なら, ここを抜ける.)

		// メッセージの変換と送出.
		TranslateMessage(&msg);	// TranslateMessageで仮想キーメッセージを文字メッセージへ変換.
		DispatchMessage(&msg);	// DispatchMessageでメッセージをウィンドウプロシージャWindowProcに送出.

	}

	// プログラムの終了
	return (int)msg.wParam;	// 終了コード(msg.wParam)を戻り値として返す.

}

// ウィンドウプロシージャWindowProcの定義
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// スタティック変数の初期化.
	static HWND hPicture = NULL;	// ピクチャーコントロールハンドルhPictureをNULLで初期化.
	static HBITMAP hBitmap = NULL;	// ビットマップハンドルhBitmapをNULLで初期化.
	static BITMAP bitmap = {0};	// BITMAP構造体オブジェクトbitmapを{0}で初期化.
	static HDC hMemDC = NULL;	// メモリデバイスコンテキストハンドルhMemDCをNULLで初期化.
	static int iHScrollPos = 0;	// iHScrollPosを0で初期化.
	static int iVScrollPos = 0;	// iVScrollPosを0で初期化.
	static int iWidth = 0;	// クライアント領域幅iWidth.
	static int iHeight = 0;	// クライアント領域高さiHeight.
	static SCROLLINFO scrollInfo = {0};	// スクロール情報構造体scrollInfoを{0}で初期化.
	static WNDPROC lpfnWndProc = NULL;	// 既定のウィンドウプロシージャlpfnWndProcをNULLで初期化.

	// ウィンドウメッセージの処理.
	switch (uMsg){	// uMsgの値ごとに処理を振り分ける.

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// 変数の宣言
				LPCREATESTRUCT lpCS;	// CreateStruct構造体ポインタlpCS.

				// lpCSの取得.
				lpCS = (LPCREATESTRUCT)lParam;	// lParamをLPCREATESTRUCTにキャストして, lpCSに格納.

				// ピクチャーコントロールの作成
				//hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_REALSIZEIMAGE, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindowでピクチャーコントロールhPictureを作成.(ウィンドウクラス名は"Static".SS_REALSIZEIMAGEなので画像サイズに合わせてコントロールのサイズも変化.)
				hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SS_BITMAP | SS_REALSIZECONTROL, 0, 0, iWidth, iHeight, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindowでピクチャーコントロールhPictureを作成.(ウィンドウクラス名は"Static".SS_REALSIZECONTROLなのでコントロールサイズに合わせて画像が拡大縮小される.)

				// ピクチャーコントロール既定のウィンドウプロシージャを取得し, WindowProcに差し替える.
				lpfnWndProc = (WNDPROC)GetWindowLong(hPicture, GWL_WNDPROC);	// GetWindowLongでプロシージャlpfnWndProcを取得.
				SetWindowLong(hPicture, GWL_WNDPROC, (LONG)WindowProc);	// SetWindowLongでWindowProcをセット.

				// スクロールバー設定.
				// 水平方向の設定.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズはsizeof(SCROLLINFO).
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// 設定する項目のフラグはページとレンジ.
				scrollInfo.nPage = 0;	// 最初は0.
				scrollInfo.nMin = 0;	// 最小値は0.
				scrollInfo.nMax = 0;	// 最初は0.
				SetScrollInfo(hPicture, SB_HORZ, &scrollInfo, FALSE);	// SetScrollInfoでscrollInfoをセット.
				// 垂直方向の設定.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズはsizeof(SCROLLINFO).
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// 設定する項目のフラグはページとレンジ.
				scrollInfo.nPage = 0;	// 最初は0.
				scrollInfo.nMin = 0;	// 最小値は0.
				scrollInfo.nMax = 0;	// 最初は0.
				SetScrollInfo(hPicture, SB_VERT, &scrollInfo, FALSE);	// SetScrollInfoでscrollInfoをセット.

				// 常にウィンドウ作成に成功するものとする.
				return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// メモリデバイスコンテキストの破棄.
				if (hMemDC != NULL){	// hMemDCがNULLでなければ.
					// 削除.
					DeleteDC(hMemDC);	// DeleteDCでhMemDCを解放.
					hMemDC = NULL;	// hMemDCにNULLをセット.
				}
				// ビットマップが残っていたら削除.
				if (hBitmap != NULL){	// hBitmapがNULLでない.
					// 削除.
					DeleteObject(hBitmap);	// DeleteObjectでhBitmapを削除.
					hBitmap = NULL;	// hBitmapにNULLをセット.
				}

				// 終了メッセージの送信.
				PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウサイズが変更された時.
		case WM_SIZE:

			// WM_SIZEブロック
			{

				// 外側のウィンドウの場合.
				if (hwnd != hPicture){	// hwndとhPictureが同じでない時.

					// クライアント領域の変更後のサイズを取得.
					iWidth = LOWORD(lParam);	// LOWORD(lParam)でクライアント領域の幅を取得し, iWidthに格納.
					iHeight = HIWORD(lParam);	// HIWORD(lParam)でクライアント領域の高さを取得し, iHeightに格納.

					// ウィンドウのサイズ変更.
					MoveWindow(hPicture, 0, 0, iWidth, iHeight, TRUE);	// MoveWindowでhPictureのサイズをクライアント領域と同じにする.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 画面の描画を要求された時.
		case WM_PAINT:

			// WM_PAINTブロック
			{

				// hPictureの時はこちらで描画.
				if (hwnd == hPicture){	// hwndとhPictureが同じ時.

					// 変数の初期化.
					HDC hDC = NULL;	// hDCをNULLで初期化.
					PAINTSTRUCT ps = {0};	// psを{0}で初期化.
					HBITMAP hOld = NULL;	// hOldをNULLで初期化.
					int iDrawWidth;	// 実際の描画幅.
					int iDrawHeight;	// 実際の描画高さ.

					// 描画開始.
					hDC = BeginPaint(hwnd, &ps);	// BeginPaintで描画開始.

					// ビットマップの選択.
					hOld = (HBITMAP)SelectObject(hMemDC, hBitmap);	// SelectObjectでhMemDCにhBitmapを選択.
					
					// ビット転送.
					iDrawWidth = iWidth - SCROLLBAR_THICKNESS;	// 描画幅 = ピクチャーコントロール幅 - スクロールバー幅.
					iDrawHeight = iHeight - SCROLLBAR_THICKNESS;	// 描画高さ = ピクチャーコントロール高さ - スクロールバー高さ.
					BitBlt(hDC, 0, 0, iDrawWidth, iDrawHeight, hMemDC, iHScrollPos, iVScrollPos, SRCCOPY);	// BitBltでhMemDCをhDCに転送.

					// 古いビットマップを再選択して戻す.
					SelectObject(hMemDC, hOld);	// SelectObjectでhOldを選択.

					// スクロールバー設定.
					// 水平方向.
					ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでscrollInfoをクリア.
					scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
					scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
					scrollInfo.nPage = iDrawWidth;	// 描画幅
					scrollInfo.nMin = 0;	// 最小値
					scrollInfo.nMax = bitmap.bmWidth;	//最大値
					SetScrollInfo(hwnd, SB_HORZ, &scrollInfo, FALSE);	// SetScrollInfoでセット.
					// 垂直方向.
					ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでscrollInfoをクリア.
					scrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
					scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
					scrollInfo.nPage = iDrawHeight;	// 描画高さ
					scrollInfo.nMin = 0;	// 最小値
					scrollInfo.nMax = bitmap.bmHeight;	//最大値
					SetScrollInfo(hwnd, SB_VERT, &scrollInfo, FALSE);	// SetScrollInfoでセット.

					// 描画終了.
					EndPaint(hwnd, &ps);	// EndPaintで描画終了.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// コマンドが発生した時.
		case WM_COMMAND:

			// WM_COMMANDブロック
			{

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
							ofn.hwndOwner = hwnd;	// hwndをセット.
							ofn.lpstrFilter = _T("ビットマップ画像(*.bmp)\0*.bmp\0すべてのファイル(*.*)\0*.*\0\0");	// ビットマップ画像とすべてのファイルのフィルタをセット.
							ofn.lpstrFile = tszPath;	// tszPathをセット.
							ofn.nMaxFile = _MAX_PATH;	// _MAX_PATHをセット.
							ofn.Flags = OFN_FILEMUSTEXIST;	// ファイルが存在しないと抜けられない.
							// "開く"ファイルダイアログの表示.
							BOOL bRet = GetOpenFileName(&ofn);	// GetOpenFileNameでファイルダイアログを表示し, 選択されたファイル名を取得する.(戻り値をbRetに格納.)
							if (bRet){	// 正常に選択された.

								// ビットマップが既にロード済みの場合.
								if (hBitmap != NULL){	// hBitmapがNULLでない.
									// 一旦削除.
									DeleteObject(hBitmap);	// DeleteObjectでhBitmapを削除.
									hBitmap = NULL;	// hBitmapにNULLをセット.
								}

								// ビットマップのロード.
								HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);	// GetWindowLongでアプリケーションインスタンスハンドルhInstanceを取得.
								hBitmap = (HBITMAP)LoadImage(hInstance, tszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// LoadImageでビットマップをロード.

								// 画像の幅と高さを取得.
								ZeroMemory(&bitmap, sizeof(BITMAP));	// ZeroMemoryでbitmapを0で初期化.
								GetObject(hBitmap, sizeof(BITMAP), &bitmap);	// GetObjectでhBitmapからBITMAP構造体を取得.
								
								// デバイスコンテキストハンドルの初期化.
								HDC hDC = NULL;	// hDCをNULLで初期化.

								// デバイスコンテキストハンドルの取得.
								hDC = GetDC(hPicture);	// GetDCでhPictureのデバイスコンテキストhDCを取得.

								// いったんメモリデバイスコンテキストの破棄.
								if (hMemDC != NULL){	// hMemDCがNULLでなければ.
									DeleteDC(hMemDC);	// DeleteDCでhMemDCを解放.
									hMemDC = NULL;	// hMemDCにNULLをセット.
								}

								// メモリデバイスコンテキストの作成.
								hMemDC = CreateCompatibleDC(hDC);	// CreateCompatibleDCでhDCからhMemDCを作成.

								// ビットマップの表示.
								SendMessage(hPicture, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);	// SendMessageでSTM_SETIMAGEを送ることでhBitmapを表示.

								// デバイスコンテキストの解放.
								ReleaseDC(hPicture, hDC);	// ReleaseDCでhDCを解放.

								// 無効領域を作成して画面の更新.
								InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRectで更新.

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
							ofn.hwndOwner = hwnd;	// hwndをセット.
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
								bi.bmiHeader.biWidth = bitmap.bmWidth;	// 画像幅bitmap.bmWidthをセット.
								bi.bmiHeader.biHeight = bitmap.bmHeight;	// 画像高さbitmap.bmHeightをセット.
								bi.bmiHeader.biPlanes = 1;	// 1をセット.
								bi.bmiHeader.biCompression = BI_RGB;	// RGB.

								// DDBからDIBのピクセル列を取得.
								hDC = GetDC(hPicture);	// GetDCでhPictureのデバイスコンテキストhDCを取得.
								GetDIBits(hDC, hBitmap, 0, bitmap.bmHeight, NULL, &bi, DIB_RGB_COLORS);	// GetDIBitsでピクセル列のサイズ(bi.bmiHeader.biSizeImage)を取得.
								lpBitsPixel = new BYTE[bi.bmiHeader.biSizeImage];	// ピクセル列用のメモリ確保.
								GetDIBits(hDC, hBitmap, 0, bitmap.bmHeight, lpBitsPixel, &bi, DIB_RGB_COLORS);	// GetDIBitsでピクセル列を取得.
								ReleaseDC(hPicture, hDC);	// hDCをリリース.

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

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 水平方向のスクロールが発生した時.
		case WM_HSCROLL:

			// WM_HSCROLLブロック
			{
				
				// hwndがhPictureの時は, 最終的には元々のウィンドウプロシージャに任せる.
				if (hwnd == hPicture){	// hwndとhPictureが同じ時.

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
					return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProcでlpfnWndProcに任せる.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 垂直方向のスクロールが発生した時.
		case WM_VSCROLL:

			// WM_VSCROLLブロック
			{
				
				// hwndがhPictureの時は, 最終的には元々のウィンドウプロシージャに任せる.
				if (hwnd == hPicture){	// hwndとhPictureが同じ時.

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
					return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProcでlpfnWndProcに任せる.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 上記以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// あとは既定の処理に任せる.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 戻り値も含めてDefWindowProcに既定の処理を任せる.

}
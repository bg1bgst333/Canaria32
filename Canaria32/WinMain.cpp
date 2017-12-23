// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
// 独自のヘッダ
#include "resource.h"	// リソース

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
				hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_REALSIZECONTROL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindowでピクチャーコントロールhPictureを作成.(ウィンドウクラス名は"Static".SS_REALSIZECONTROLなのでコントロールサイズに合わせて画像が拡大縮小される.)

				// 常にウィンドウ作成に成功するものとする.
				return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

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

								// ビットマップの表示.
								SendMessage(hPicture, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);	// SendMessageでSTM_SETIMAGEを送ることでhBitmapを表示.
							
							}

						}

						// 既定の処理へ向かう.
						break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

					// "名前を付けて保存(&A)..."
					case ID_FILE_SAVE_AS:

						// ID_FILE_SAVE_ASブロック
						{

							// メッセージボックスで"ID_FILE_SAVE_AS"と表示.
							MessageBox(NULL, _T("ID_FILE_SAVE_AS"), _T("Canaria"), MB_OK | MB_ICONASTERISK);	// MessageBoxで"ID_FILE_SAVE_AS"と表示.

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

		// 上記以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// あとは既定の処理に任せる.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 戻り値も含めてDefWindowProcに既定の処理を任せる.

}
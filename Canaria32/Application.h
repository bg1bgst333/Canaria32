// 二重インクルード防止
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

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

// アプリケーションクラスCApplication
class CApplication{

	// publicメンバ
	public:

		// publicメンバ関数
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// インスタンス初期化関数InitInstance.
		virtual int Run();	// メッセージループ処理関数Run.
		virtual int ExitInstance();	// 終了処理関数ExitInstance.

};

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc.

#endif
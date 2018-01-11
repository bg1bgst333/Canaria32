// ヘッダのインクルード
// 独自のヘッダ
#include "Application.h"	// CApplication

// メッセージループ処理関数Run.
int CApplication::Run(){

	// 構造体の宣言.
	MSG msg;	// MSG型メッセージ構造体msg

	// メッセージループの処理
	while (GetMessage(&msg, NULL, 0, 0) > 0){	// GetMessageでウィンドウメッセージを取得し, msgに格納.(0以下なら, ここを抜ける.)

		// メッセージの変換と送出.
		TranslateMessage(&msg);	// TranslateMessageで仮想キーメッセージを文字メッセージへ変換.
		DispatchMessage(&msg);	// DispatchMessageでメッセージをウィンドウプロシージャWindowProcに送出.

	}

	// ExitInstanceの値を返す.
	return ExitInstance();	// returnでExitInstanceを返す.

}

// 終了処理関数ExitInstance.
int CApplication::ExitInstance(){

	// 今回は常に0を返す.
	return 0;	// returnで0を返す.

}
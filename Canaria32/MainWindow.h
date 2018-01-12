// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow

// マクロの定義
#define SCROLLBAR_THICKNESS 16	// とりあえずスクロールバーの厚さはマクロで16としておく.

// メインウィンドウクラスCMainWindow
class CMainWindow : public CWindow{

	// privateメンバ
	private:

		// privateメンバ変数
		HWND m_hPicture;	// ピクチャーコントロールハンドル.
		//SCROLLINFO m_scrollInfo;	// スクロールバー情報.
		int m_iWidth;	// クライアント領域幅.
		int m_iHeight;	// クライアント領域高さ.
		HBITMAP m_hBitmap;	// ビットマップハンドル.
		BITMAP m_Bitmap;	// BITMAP構造体オブジェクト.
		HDC m_hMemDC;	// メモリデバイスコンテキストハンドル.

	// publicメンバ
	public:

		// publicメンバ変数
		// staticメンバ変数
		static WNDPROC m_lpfnWndProc;	// ピクチャーコントロール既定のウィンドウプロシージャ.
		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static LRESULT CALLBACK PictureProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// スタティックウィンドウプロシージャPictureProc.(ピクチャーコントロールのプロシージャ差し替え先.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	// コマンドが発生した時.

};

#endif
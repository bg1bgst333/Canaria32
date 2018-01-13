// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "MenuWindow.h"	// CMenuWindow
#include "Picture.h"	// CPicture

// マクロの定義
#define SCROLLBAR_THICKNESS 16	// とりあえずスクロールバーの厚さはマクロで16としておく.

// メインウィンドウクラスCMainWindow
class CMainWindow : public CMenuWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrCurrentFileName;	// 現在読み込んでいるファイル名.(フルパス)
		tstring m_tstrCurrentFileNameTitle;	// 現在読み込んでいるファイル名.(フルパスの中のファイル名部分だけ.)
		CPicture *m_pPicture;	// ピクチャーコントロール.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName);	// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		void SetCurrentFileName(LPCTSTR lpctszFileName);	// ファイル読み書きしたら, これでファイルパスをセット.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "開く"を選択された時のハンドラ.
		virtual int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "名前を付けて保存"を選択された時のハンドラ.

};

#endif
// 二重インクルード防止
#ifndef __FILE_DIALOG_H__
#define __FILE_DIALOG_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
#include <string>	// std::string

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// ファイルダイアログクラスCFileDialog
class CFileDialog{

	// privateメンバ
	private:

		// privateメンバ関数
		void SetFilter(LPCTSTR lpctszFilter);	// フィルタのセット.

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrPath;	// ファイルパスm_tstrPath.
		tstring m_tstrDefFileName;	// デフォルトファイル名m_tstrDefFileName.
		tstring m_tstrExt;	// 拡張子m_tstrExt.
		TCHAR *m_ptszFilter;	// フィルタ文字列へのポインタm_ptszFilter.
		DWORD m_dwFlags;	// フラグm_dwFlags.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags);	// コンストラクタには, デフォルトファイル名, 拡張子, フィルタ, フラグを指定する.
		virtual ~CFileDialog();	// デストラクタ.
		// メンバ関数
		BOOL ShowOpenFileDialog(HWND hWnd);	// "開く"ファイルダイアログの表示ShowOpenFileDialog.
		BOOL ShowSaveFileDialog(HWND hWnd);	// "名前を付けて保存"ファイルダイアログの表示ShowSaveFileDialog.
		
};

#endif
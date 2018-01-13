// ヘッダのインクルード
// 独自のヘッダ
#include "FileDialog.h"	// CFileDialog
#include "c_string_utility.h"	// class_c_string_utility

// コンストラクタには, デフォルトファイル名, 拡張子, フィルタ, フラグを指定する.
CFileDialog::CFileDialog(LPCTSTR lpctszDefFileName, LPCTSTR lpctszExt, LPCTSTR lpctszFilter, DWORD dwFlags){

	// メンバのセット.
	// デフォルトファイル名.
	if (lpctszDefFileName == NULL || _tcscmp(lpctszDefFileName, _T("")) == 0){	// NULLまたは空文字列の場合.
		m_tstrDefFileName = _T("*.");	// "*."をセット.
		m_tstrDefFileName = m_tstrDefFileName + lpctszExt;	// lpctszExtを連結. 
	}
	else{	// そうでない場合.
		m_tstrDefFileName = lpctszDefFileName;	// デフォルトファイル名lpctszDefFileNameをセット.
	}
	// デフォルト拡張子.
	if (lpctszExt == NULL){	// NULLなら.
		m_tstrExt = _T("");	// m_tstrExtに""をセット.
	}
	else{	// そうでない場合.
		m_tstrExt = lpctszExt;	// デフォルト拡張子lpctszExtをセット.
	}
	// フィルタ.
	m_ptszFilter = NULL;	// m_ptszFilterにm_ptszFilterをセット.
	SetFilter(lpctszFilter);	// SetFilterでフィルタをセット.
	// フラグ.
	m_dwFlags = dwFlags;	// m_dwFlagsにdwFlagsをセット.

}

// デストラクタ.
CFileDialog::~CFileDialog(){

	// フィルタ配列の解放.
	delete[] m_ptszFilter;	// delete[]でm_ptszFilterを解放.
	m_ptszFilter = NULL;	// m_ptszFilterをNULLにセット.

}

// フィルタのセット.
void CFileDialog::SetFilter(LPCTSTR lpctszFilter){	// フィルタのセット.

	// 長さを取得.
	size_t len = _tcslen(lpctszFilter);	// フィルタの長さを取得.
	m_ptszFilter = new TCHAR[len + 1];	// フィルタ配列の確保.
	wmemset(m_ptszFilter, _T('\0'), len + 1);	// '\0'で埋める.
	_tcscpy(m_ptszFilter, lpctszFilter);	// フィルタのコピー.
	class_c_string_utility::wmemreplace(m_ptszFilter, len, _T('|'), _T('\0'));	// class_c_string_utility::wmemreplaceで'|'を'\0'に置換.

}

// "開く"ファイルダイアログの表示ShowOpenFileDialog.
BOOL CFileDialog::ShowOpenFileDialog(HWND hWnd){

	// 変数の宣言・初期化.
	OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.
	TCHAR *ptszPath = new TCHAR[_MAX_PATH];	// TCHAR動的配列を作成し, ptszPathに格納.
	
	// デフォルトファイル名をセット.
	wmemset(ptszPath, _T('\0'), _MAX_PATH);	// wmemsetで0で埋める.
	_tcscpy(ptszPath, m_tstrDefFileName.c_str());	// デフォルトファイル名をptszPathにセット.

	// ofnに値をセット.
	ofn.lStructSize = sizeof(OPENFILENAME);	// 構造体のサイズ.
	ofn.hwndOwner = hWnd;	// オーバーウィンドウ.
	ofn.lpstrFile = ptszPath;	// デフォルトパス.
	ofn.nMaxFile = _MAX_PATH;	// MAXは_MAX_PATH(260).
	ofn.lpstrDefExt = m_tstrExt.c_str();	// デフォルト拡張子.
	ofn.lpstrFilter = m_ptszFilter;	// フィルタ.
	ofn.Flags = m_dwFlags;	// フラグ.

	// ファイル選択.
	if (!GetOpenFileName(&ofn)){	// GetOpenFileNameでファイルを選択.

		// 選択しなかった場合.(キャンセル)
		delete[] ptszPath;	// delete[]でptszPathを解放.
		m_tstrPath = _T("");	// m_tstrPathに""をセット.
		return FALSE;	// 処理してないのでFALSEを返す.

	}

	// パスを格納.
	m_tstrPath = ptszPath;	// ptszPathをm_tstrPathに代入.

	// バッファを解放.
	delete[] ptszPath;	// delete[]でptszPathを解放.

	// 処理したのでTRUEを返す.
	return TRUE;	// 処理したので戻り値としてTRUEを返す.

}

// "名前を付けて保存"ファイルダイアログの表示ShowSaveFileDialog.
BOOL CFileDialog::ShowSaveFileDialog(HWND hWnd){

	// 変数の宣言・初期化.
	OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.
	TCHAR *ptszPath = new TCHAR[_MAX_PATH];	// TCHAR動的配列を作成し, ptszPathに格納.
	
	// デフォルトファイル名をセット.
	wmemset(ptszPath, _T('\0'), _MAX_PATH);	// wmemsetで0で埋める.
	_tcscpy(ptszPath, m_tstrDefFileName.c_str());	// デフォルトファイル名をptszPathにセット.

	// ofnに値をセット.
	ofn.lStructSize = sizeof(OPENFILENAME);	// 構造体のサイズ.
	ofn.hwndOwner = hWnd;	// オーバーウィンドウ.
	ofn.lpstrFile = ptszPath;	// デフォルトパス.
	ofn.nMaxFile = _MAX_PATH;	// MAXは_MAX_PATH(260).
	ofn.lpstrDefExt = m_tstrExt.c_str();	// デフォルト拡張子.
	ofn.lpstrFilter = m_ptszFilter;	// フィルタ.
	ofn.Flags = m_dwFlags;	// フラグ.

	// ファイル選択.
	if (!GetSaveFileName(&ofn)){	// GetSaveFileNameでファイルを選択.

		// 選択しなかった場合.(キャンセル)
		delete[] ptszPath;	// delete[]でptszPathを解放.
		m_tstrPath = _T("");	// m_tstrPathに""をセット.
		return FALSE;	// 処理してないのでFALSEを返す.

	}

	// パスを格納.
	m_tstrPath = ptszPath;	// ptszPathをm_tstrPathに代入.

	// バッファを解放.
	delete[] ptszPath;	// delete[]でptszPathを解放.

	// 処理したのでTRUEを返す.
	return TRUE;	// 処理したので戻り値としてTRUEを返す.

}
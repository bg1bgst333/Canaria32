// ヘッダのインクルード
// 独自のヘッダ
#include "CustomControl.h"	// CCustomControl

// staticメンバ変数の定義
std::map<tstring, WNDPROC>	CCustomControl::m_mapBaseWindowProcMap;	// ベースウィンドウプロシージャマップm_mapBaseWindowProcMap

// スタティックウィンドウプロシージャStaticWindowProc.
LRESULT CALLBACK CCustomControl::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// ポインタの初期化
	CWindow *pWindow = NULL;	// CWindowオブジェクトポインタpWindowをNULLに初期化.

	// hwndでCWindowオブジェクトポインタが引けたら, pWindowに格納.
	if (m_mapWindowMap.find(hwnd) != m_mapWindowMap.end()){	// findでキーをhwndとするCWindowオブジェクトポインタが見つかったら.
		pWindow = m_mapWindowMap[hwnd];	// pWindowにhwndで引けるCWindowオブジェクトポインタを格納.
	}

	// ウィンドウオブジェクトを取得できない場合.
	if (pWindow == NULL){	// pWindowがNULLの時.

		// 配列の初期化
		TCHAR tszClassName[256] = {0};	// tszClassNameを0で初期化.

		// ウィンドウハンドルからウィンドウクラス名を取得.
		GetClassName(hwnd, tszClassName, 256);	// GetClassNameでウィンドウクラス名を取得.

		// tszClassNameがm_mapBaseWindowProcMapのキーにあれば.
		if (m_mapBaseWindowProcMap.find(tszClassName) != m_mapBaseWindowProcMap.end()){	// みつかったら.

			// 既定のプロシージャに任せる.
			return CallWindowProc(m_mapBaseWindowProcMap[tszClassName], hwnd, uMsg, wParam, lParam);	// CallWindowProcで, このメッセージをm_mapBaseWindowProcMap[tszClassName]に任せる.

		}
		else{	// 無い場合.

			// そうでないなら, DefWindowProcに任せる.
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProcの値を返す.

		}

	}
	else{	// pWindowがあった場合.

		// そのウィンドウのDynamicWindowProcに任せる.
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);	// pWindow->DynamicWindowProcに渡す.

	}

}

// ウィンドウ作成関数Create.
BOOL CCustomControl::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの位置・サイズをセット.
	m_x = x;				// m_xにxを代入.
	m_y = y;				// m_yにyを代入.
	m_iWidth = iWidth;		// m_iWidthにiWidthを代入.
	m_iHeight = iHeight;	// m_iHeight = iHeightを代入.

	// ウィンドウの作成
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, this);	// CreateWindowでウィンドウを作成し, ハンドルをm_hWndに格納.(最後の引数にthisを渡す.)
	if (m_hWnd == NULL){	// m_hWndがNULLなら失敗.

		// 失敗ならFALSE
		return FALSE;	// FALSEを返す.

	}

	// GetWindowRectで生成後のRECTを取得し, 改めてサイズをセット.
	RECT rc = {0};	// rcを{0}で初期化.
	GetWindowRect(m_hWnd, &rc);	// GetWindowRectでrcを取得.
	m_x = rc.left;	// m_xにrc.leftをセット.
	m_y = rc.top;	// m_yにrc.topをセット.
	m_iWidth = rc.right - rc.left;	// m_iWidthにrc.right - rc.leftをセット.
	m_iHeight = rc.bottom - rc.top;	// m_iHeightにrc.bottom - rc.topをセット.

	// OnCreateは以降は呼ばれないので, ここで呼んでおく.
	CREATESTRUCT cs;	// CREATESTRUCTを一応用意.
	cs.hInstance = hInstance;	// hInstanceは要るかもしれないので, これは渡せるようにしておく.
	if (OnCreate(m_hWnd, &cs) != 0){	// OnCreateにm_hWndとcsを渡す.

		// 戻り値が0でなければ失敗なので, ウィンドウを破棄する.
		DestroyWindow(m_hWnd);	// DestroyWindowでm_hWndを破棄.
		m_hWnd = NULL;	// m_hWndにNULLをセット.
		return FALSE;	// FALSEを返す.

	}

	// 既定のウィンドウプロシージャを取得し, CCustomControl::StaticWindowProcに差し替える.
	WNDPROC lpfnWndProc;	// 既定のプロシージャlpfnWndProc
	lpfnWndProc = (WNDPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);	// GetWindowLongでプロシージャlpfnWndProcを取得.
	SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)StaticWindowProc);	// SetWindowLongでプロシージャCCustomControl::StaticWindowProcを設定.

	// マップのキーにウィンドウクラス名がなければ登録.
	if (m_mapBaseWindowProcMap.find(lpctszClassName) == m_mapBaseWindowProcMap.end()){	// マップに無い時.
		m_mapBaseWindowProcMap.insert(std::pair<tstring, WNDPROC>(lpctszClassName, lpfnWndProc));	// プロシージャを登録.
	}

	// WM_CREATEを通らないので, ウィンドウマップの登録も行う.
	if (m_mapWindowMap.find(m_hWnd) == m_mapWindowMap.end()){	// ウィンドウマップになければ.
		m_mapWindowMap.insert(std::pair<HWND, CWindow *>(m_hWnd, this));	// 登録する.
	}

	// 成功ならTRUE.
	return TRUE;	// TRUEを返す.

}

// ダイナミックウィンドウプロシージャDynamicWindowProc.
LRESULT CCustomControl::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// ウィンドウメッセージの処理
	switch (uMsg){	// uMsgの値ごとに処理を振り分ける.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// OnDestroyに任せる.
				OnDestroy();	// OnDestroyを呼ぶ.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// ウィンドウのサイズが変更された時.
		case WM_SIZE:

			// WM_SIZEブロック
			{

				// 変数の初期化
				UINT nType = (UINT)wParam;	// UINT型nTypeにwParamをセット.
				int cx = LOWORD(lParam);	// int型cxにLOWORD(lParam)をセット.
				int cy = HIWORD(lParam);	// int型cyにHIWORD(lParam)をセット.

				// OnSizeに任せる.
				OnSize(nType, cx, cy);	// OnSizeにhwnd, nType, cx, cyを渡す.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// 画面の描画を要求された時.
		case WM_PAINT:

			// WM_PAINTブロック
			{

				// OnPaintに任せる.
				OnPaint();	// OnPaintを呼ぶ.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// これらのメッセージはDefWindowProcに投げないと, 正しく動作しない.
		case WM_NCHITTEST:
		case WM_NCLBUTTONDOWN:
		case WM_NCLBUTTONUP:

			// DefWindowProcに任せる.
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 引数をDefWindowProcに渡し, 戻り値をそのまま返す.

		// 水平方向のスクロールが発生した時.
		case WM_HSCROLL:

			// WM_HSCROLLブロック
			{
				
				// OnHScrollに任せる.
				OnHScroll(LOWORD(wParam), HIWORD(wParam));	// OnHScrollに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// 垂直方向のスクロールが発生した時.
		case WM_VSCROLL:

			// WM_VSCROLLブロック
			{

				// OnVScrollに任せる.
				OnVScroll(LOWORD(wParam), HIWORD(wParam));	// OnVScrollに任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// マウスの移動時.
		case WM_MOUSEMOVE:

			// WM_MOUSEMOVEブロック
			{

				// 変数の宣言
				POINT pt;	// POINT構造体変数pt.

				// 座標の取り出し.
				pt.x = LOWORD(lParam);	// lParamの下位ワードが座標x.
				pt.y = HIWORD(lParam);	// lParamの上位ワードが座標y.

				// OnMouseMoveに任せる.
				OnMouseMove(wParam, pt);	// OnMouseMoveにwParamとptを渡す.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// マウスの左ボタンが押された時.
		case WM_LBUTTONDOWN:

			// WM_LBUTTONDOWNブロック
			{

				// 変数の宣言
				POINT pt;	// POINT構造体変数pt.

				// 座標の取り出し.
				pt.x = LOWORD(lParam);	// lParamの下位ワードが座標x.
				pt.y = HIWORD(lParam);	// lParamの上位ワードが座標y.

				// OnLButtonDownに任せる.
				OnLButtonDown(wParam, pt);	// OnLButtonDownにwParamとptを渡す.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// マウスの左ボタンが離されたとき.
		case WM_LBUTTONUP:

			// WM_LBUTTONUPブロック
			{

				// 変数の宣言
				POINT pt;	// POINT構造体変数pt.

				// 座標の取り出し.
				pt.x = LOWORD(lParam);	// lParamの下位ワードが座標x.
				pt.y = HIWORD(lParam);	// lParamの上位ワードが座標y.

				// OnLButtonUpに任せる.
				OnLButtonUp(wParam, pt);	// OnLButtonUpにwParamとptを渡す.

			}
			
			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

		// それ以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理へ向かう.

	}

	// 配列の初期化
	TCHAR tszClassName[256] = {0};	// tszClassNameを0で初期化.

	// ウィンドウハンドルからウィンドウクラス名を取得.
	GetClassName(hwnd, tszClassName, 256);	// GetClassNameでウィンドウクラス名を取得.

	// tszClassNameがm_mapBaseWindowProcMapのキーにあれば.
	if (m_mapBaseWindowProcMap.find(tszClassName) != m_mapBaseWindowProcMap.end()){	// みつかったら.

		// 既定のプロシージャに任せる.
		return CallWindowProc(m_mapBaseWindowProcMap[tszClassName], hwnd, uMsg, wParam, lParam);	// CallWindowProcで, このメッセージをm_mapBaseWindowProcMap[tszClassName]に任せる.

	}
	else{	// 無い場合.

		// そうでないなら, DefWindowProcに任せる.
		return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProcの値を返す.

	}

}

// ウィンドウが破棄された時.
void CCustomControl::OnDestroy(){

	// 自分のウィンドウハンドルが残っていたらマップから削除.
	if (m_mapWindowMap.find(m_hWnd) != m_mapWindowMap.end()){	// findでみつかったら.
		m_mapWindowMap.erase(m_hWnd);	// m_mapWindowMap.eraseで削除.
	}

}

// 画面の描画を要求された時.
void CCustomControl::OnPaint(){

}

// 水平方向スクロールバーのイベントが発生した時.
void CCustomControl::OnHScroll(UINT nSBCode, UINT nPos){

}

// 垂直方向スクロールバーのイベントが発生した時.
void CCustomControl::OnVScroll(UINT nSBCode, UINT nPos){

}

// マウスが移動している時.
void CCustomControl::OnMouseMove(UINT nFlags, POINT pt){

}

// マウスの左ボタンが押された時.
void CCustomControl::OnLButtonDown(UINT nFlags, POINT pt){

}

// マウスの左ボタンが離された時.
void CCustomControl::OnLButtonUp(UINT nFlags, POINT pt){

}
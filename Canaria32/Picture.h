// 二重インクルード防止
#ifndef __PICTURE_H__
#define __PICTURE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "CustomControl.h"	// CCustomControl

// マクロ定義
#define SCROLLBAR_THICKNESS 16	// とりあえずスクロールバーの厚さはマクロで16としておく.

// ピクチャーコントロールクラスCPicture
class CPicture : public CCustomControl {

	// publicメンバ
	public:

		// publicメンバ変数
		HBITMAP m_hBitmap;	// ビットマップハンドルm_hBitmap
		BITMAP m_Bitmap;	// BITMAP構造体オブジェクト.
		tstring m_tstrImageName;	// イメージ名m_tstrImageName
		HDC m_hMemDC;	// メモリデバイスコンテキストm_hMemDC
		int m_iHScrollPos;	// スクロールバーの水平方向の位置m_iHScrollPos
		int m_iVScrollPos;	// スクロールバーの垂直方向の位置m_iVScrollPos
		SCROLLINFO m_ScrollInfo;	// スクロール情報m_ScrollInfo.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CPicture();	// コンストラクタCPicture
		virtual ~CPicture();	// デストラクタ~CPicture()
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create(ウィンドウクラス名指定バージョン.)
		BOOL LoadImage(HINSTANCE hInstance, LPCTSTR lpctszImageName);	// 画像をロードする関数LoadImage
		BOOL SaveImage(LPCTSTR lpctszImageName);	// 画像をセーブする関数SaveImage
		void SetImage();	// 画像をセット(表示)する関数SetImage
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual void OnHScroll(UINT nSBCode, UINT nPos);	// 水平方向スクロールバーイベント時のハンドラOnHScroll.
		virtual void OnVScroll(UINT nSBCode, UINT nPos);	// 垂直方向スクロールバーイベント時のハンドラOnVScroll.
		virtual void OnMouseMove(UINT nFlags, POINT pt);	// マウスが移動している時.
		virtual void OnLButtonDown(UINT nFlags, POINT pt);	// マウスの左クリックが行われた時のハンドラOnLButtonDown.
		virtual void OnLButtonUp(UINT nFlags, POINT pt);		// マウスの左ボタンが離された時.

};

#endif
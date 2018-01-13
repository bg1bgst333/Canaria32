// 二重インクルード防止
#ifndef __C_STRING_UTILITY_H__
#define __C_STRING_UTILITY_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <string.h>	// C文字列処理
#include <stdlib.h>		// C標準ユーティリティ

// C文字列処理ユーティリティクラスclass_c_string_utility
class class_c_string_utility{

	// publicメンバ
	public:

		// publicメンバ関数
		// staticメンバ関数
		static const wchar_t *wmemreplace(wchar_t *target, size_t len, wchar_t before, wchar_t after);	// メモリ領域内の文字置換.

};

#endif
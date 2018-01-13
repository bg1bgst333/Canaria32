// ヘッダのインクルード
// 独自のヘッダ
#include "c_string_utility.h"	// class_c_string_utility

// メモリ領域内の文字置換.
const wchar_t *class_c_string_utility::wmemreplace(wchar_t *target, size_t len, wchar_t before, wchar_t after){

	// targetのbeforeをafterに置換.
	for (unsigned int i = 0; i < len; i++){	// lenの数だけ繰り返す.
		if (target[i] == before){	// target[i]とbeforeが同じ場合.
			target[i] = after;	// target[i]にafterをセット.
		}
	}

	// 変換後の文字列を返す.
	return target;	// targetを返す.

}
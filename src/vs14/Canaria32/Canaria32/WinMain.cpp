// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <windows.h>	// �W��WindowsAPI
#include <tchar.h>		// TCHAR�^

// _tWinMain�֐��̒�`
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd) {

	// ���b�Z�[�W�{�b�N�X��"Canaria32"�ƕ\��.
	MessageBox(NULL, _T("Canaria32"), _T("Canaria32"), MB_OK);	// MessageBox��"Canaria32"�ƕ\��.

	// �v���O�����̐���I��
	return 0;	// 0��Ԃ��Đ���I��.

}
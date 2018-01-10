// ��d�C���N���[�h�h�~
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <stdio.h>		// C�W�����o��
#include <stdlib.h>		// C�W�����[�e�B���e�B
#include <locale.h>		// ���P�[��
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI
// �Ǝ��̃w�b�_
#include "resource.h"	// ���\�[�X

// �}�N���̒�`
#define SCROLLBAR_THICKNESS 16	// �Ƃ肠�����X�N���[���o�[�̌����̓}�N����16�Ƃ��Ă���.

// �A�v���P�[�V�����N���XCApplication
class CApplication{

	// public�����o
	public:

		// public�����o�֐�
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// �C���X�^���X�������֐�InitInstance.
		virtual int Run();	// ���b�Z�[�W���[�v�����֐�Run.
		virtual int ExitInstance();	// �I�������֐�ExitInstance.

};

// �֐��̃v���g�^�C�v�錾.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��WindowProc.

#endif
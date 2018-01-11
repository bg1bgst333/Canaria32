// ��d�C���N���[�h�h�~
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI
// �Ǝ��̃w�b�_
#include "Window.h"		// CWindow
#include "resource.h"	// ���\�[�X

// �A�v���P�[�V�����N���XCApplication
class CApplication{

	// public�����o
	public:

		// public�����o�ϐ�
		CWindow m_mainWnd;	// ���C���E�B���h�Em_mainWnd.

		// public�����o�֐�
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) = 0;	// �C���X�^���X�������֐�InitInstance.(�������z�֐�)
		virtual int Run();	// ���b�Z�[�W���[�v�����֐�Run.
		virtual int ExitInstance();	// �I�������֐�ExitInstance.

};

#endif
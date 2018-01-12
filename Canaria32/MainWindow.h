// ��d�C���N���[�h�h�~
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Window.h"	// CWindow

// �}�N���̒�`
#define SCROLLBAR_THICKNESS 16	// �Ƃ肠�����X�N���[���o�[�̌����̓}�N����16�Ƃ��Ă���.

// ���C���E�B���h�E�N���XCMainWindow
class CMainWindow : public CWindow{

	// private�����o
	private:

		// private�����o�ϐ�
		HWND m_hPicture;	// �s�N�`���[�R���g���[���n���h��.
		//SCROLLINFO m_scrollInfo;	// �X�N���[���o�[���.
		int m_iWidth;	// �N���C�A���g�̈敝.
		int m_iHeight;	// �N���C�A���g�̈捂��.
		HBITMAP m_hBitmap;	// �r�b�g�}�b�v�n���h��.
		BITMAP m_Bitmap;	// BITMAP�\���̃I�u�W�F�N�g.
		HDC m_hMemDC;	// �������f�o�C�X�R���e�L�X�g�n���h��.

	// public�����o
	public:

		// public�����o�ϐ�
		// static�����o�ϐ�
		static WNDPROC m_lpfnWndProc;	// �s�N�`���[�R���g���[������̃E�B���h�E�v���V�[�W��.
		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CMainWindow();	// �R���X�g���N�^CMainWindow()
		virtual ~CMainWindow();	// �f�X�g���N�^~CMainWindow()
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static LRESULT CALLBACK PictureProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �X�^�e�B�b�N�E�B���h�E�v���V�[�W��PictureProc.(�s�N�`���[�R���g���[���̃v���V�[�W�������ւ���.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	// �R�}���h������������.

};

#endif
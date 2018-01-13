// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <locale.h>	// ���P�[��
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// �����o�̏�����.
	m_pPicture = NULL;	// m_pPicture��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������.
	if (m_pPicture != NULL){	// m_pPicture��NULL�łȂ���.
		delete m_pPicture;	// delete��m_pPicture��j��.
		m_pPicture = NULL;	// m_pPicture��NULL���Z�b�g.
	}

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��IDR_MENU1���g��.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��o�[�W����.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[lpszMenuName���g��.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), lpszMenuName);	// ���j���[�����w�肷��.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ���j���[�o�[�̍쐬.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBar�I�u�W�F�N�gm_pMenuBar���쐬.

	// ���j���[�̃��[�h.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenu��IDR_MENU1�����[�h.

	// ���j���[�̃Z�b�g.
	m_pMenuBar->SetMenu(hwnd);	// SetMenu��hwnd�Ƀ��j���[���Z�b�g.

	// �s�N�`���[�̐���.
	m_pPicture = new CPicture();	// CPicture�I�u�W�F�N�g�𐶐�����, m_pPicture�Ɋi�[.
	m_pPicture->Create(_T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SS_REALSIZECONTROL, 0, 0, 0, 0, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pPicture->Create�Ńs�N�`���[�R���g���[�����쐬.(SS_REALSIZECONTROL�̓R���g���[���̑傫���ɍ��킹�ďk������, SS_REALSIZEIMAGE�͉摜�T�C�Y�ɍ��킹�ăR���g���[�����g�傷��.)

	// �X�N���[���o�[�ݒ�.
	// ���������̐ݒ�.
#if 0
	m_scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y��sizeof(SCROLLINFO).
	m_scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �ݒ肷�鍀�ڂ̃t���O�̓y�[�W�ƃ����W.
	m_scrollInfo.nPage = 0;	// �ŏ���0.
	m_scrollInfo.nMin = 0;	// �ŏ��l��0.
	m_scrollInfo.nMax = 0;	// �ŏ���0.
	SetScrollInfo(m_hPicture, SB_HORZ, &m_scrollInfo, FALSE);	// SetScrollInfo��m_scrollInfo���Z�b�g.
	// ���������̐ݒ�.
	m_scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y��sizeof(SCROLLINFO).
	m_scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �ݒ肷�鍀�ڂ̃t���O�̓y�[�W�ƃ����W.
	m_scrollInfo.nPage = 0;	// �ŏ���0.
	m_scrollInfo.nMin = 0;	// �ŏ��l��0.
	m_scrollInfo.nMax = 0;	// �ŏ���0.
	SetScrollInfo(m_hPicture, SB_VERT, &m_scrollInfo, FALSE);	// SetScrollInfo��m_scrollInfo���Z�b�g.
#endif

	// ���j���[�n���h���̒ǉ�.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandler��ID_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandler��ID_FILE_SAVE_AS�ɑ΂���n���h��CMainWindow::OnFileSaveAs��o�^.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandler��ID_FILE_SAVE_AS�̃n���h�����폜.

	// CWindow��OnDestroy���Ă�.
	CWindow::OnDestroy();	// CWindow::OnDestroy���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// �����o�ɃZ�b�g.
	MoveWindow(m_pPicture->m_hWnd, 0, 0, cx, cy, TRUE);	// MoveWindow��m_pPicture->m_hWnd�̃T�C�Y���N���C�A���g�̈�Ɠ����ɂ���.
	
	// �����̃T�C�Y���v��.
	RECT rc = {0};
	GetWindowRect(m_hWnd, &rc);
	m_iWidth = rc.right - rc.left;
	m_iHeight = rc.bottom - rc.top;

}

// "�J��"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("bmp"), _T("�r�b�g�}�b�v�摜(*.bmp)|*.bmp|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.

		// �C���X�^���X�n���h���̎擾.
		HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWLP_HINSTANCE);	// GetWindowLong�ŃC���X�^���X�n���h�����擾.
		// ���[�h.
		if (m_pPicture->LoadImage(hInstance, selDlg.m_tstrPath.c_str())){	// m_pPicture->LoadImage�Ń��[�h.
			// �Z�b�g.
			m_pPicture->SetImage();	// m_pPicture->SetImage�ŃZ�b�g.
		}

	}

	// �������Ă��Ȃ��̂�-1.
	return -1;	// return��-1��Ԃ�.

}

// "���O��t���ĕۑ�"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "���O��t���ĕۑ�"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("bmp"), _T("�r�b�g�}�b�v�摜(*.bmp)|*.bmp|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.
		
		// �Z�[�u.
		m_pPicture->SaveImage(selDlg.m_tstrPath.c_str());	// m_pPicture->SaveImage�ŃZ�[�u.
		
	}

	// �������Ă��Ȃ��̂�-1.
	return -1;	// return��-1��Ԃ�.

}
// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <locale.h>	// ���P�[��
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// ���\�[�X

// static�ϐ��̐錾
static CMainWindow *pMainWnd = NULL;	// static��CMainWindow�I�u�W�F�N�g�|�C���^pMainWnd��NULL�ŏ�����.

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

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

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

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

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// �I�����b�Z�[�W�̑��M.
	PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

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

// �R�}���h������������.
BOOL  CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// �R�}���h�̏���.
	switch (LOWORD(wParam)){	// LOWORD(wParam)�Ń��\�[�XID���킩��̂�, ���̒l���Ƃɏ�����U�蕪����.

		// "�J��(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPEN�u���b�N
			{

				// "�J��"�t�@�C���̑I��.
				// �\���́E�z��̏�����.
				OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.
				TCHAR tszPath[_MAX_PATH] = {0};	// �t�@�C���p�XtszPath��{0}�ŏ�����.
				// �p�����[�^�̃Z�b�g.
				ofn.lStructSize = sizeof(OPENFILENAME);	// sizeof��OPENFILENAME�\���̂̃T�C�Y���Z�b�g.
				ofn.hwndOwner = m_hWnd;	// m_hWnd���Z�b�g.
				ofn.lpstrFilter = _T("�r�b�g�}�b�v�摜(*.bmp)\0*.bmp\0���ׂẴt�@�C��(*.*)\0*.*\0\0");	// �r�b�g�}�b�v�摜�Ƃ��ׂẴt�@�C���̃t�B���^���Z�b�g.
				ofn.lpstrFile = tszPath;	// tszPath���Z�b�g.
				ofn.nMaxFile = _MAX_PATH;	// _MAX_PATH���Z�b�g.
				ofn.Flags = OFN_FILEMUSTEXIST;	// �t�@�C�������݂��Ȃ��Ɣ������Ȃ�.
				// "�J��"�t�@�C���_�C�A���O�̕\��.
				BOOL bRet = GetOpenFileName(&ofn);	// GetOpenFileName�Ńt�@�C���_�C�A���O��\����, �I�����ꂽ�t�@�C�������擾����.(�߂�l��bRet�Ɋi�[.)
				if (bRet){	// ����ɑI�����ꂽ.

					// �C���X�^���X�n���h���̎擾.
					HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWLP_HINSTANCE);	// GetWindowLong�ŃC���X�^���X�n���h�����擾.
					// ���[�h.
					if (m_pPicture->LoadImage(hInstance, tszPath)){	// m_pPicture->LoadImage�Ń��[�h.
						// �Z�b�g.
						m_pPicture->SetImage();	// m_pPicture->SetImage�ŃZ�b�g.
					}

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// "���O��t���ĕۑ�(&A)..."
		case ID_FILE_SAVE_AS:

			// ID_FILE_SAVE_AS�u���b�N
			{

				// "���O��t���ĕۑ�"����t�@�C���̑I��.
				// �\���́E�z��̏�����.
				OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.
				TCHAR tszPath[_MAX_PATH] =  {0};	// �t�@�C���p�XtszPath��{0}�ŏ�����.
				// �p�����[�^�̃Z�b�g.
				ofn.lStructSize = sizeof(OPENFILENAME);	// sizeof��OPENFILENAME�\���̂̃T�C�Y���Z�b�g.
				ofn.hwndOwner = m_hWnd;	// m_hWnd���Z�b�g.
				ofn.lpstrFilter = _T("�r�b�g�}�b�v�摜(*.bmp)\0*.bmp\0���ׂẴt�@�C��(*.*)\0*.*\0\0");	// �r�b�g�}�b�v�摜�Ƃ��ׂẴt�@�C���̃t�B���^���Z�b�g.
				ofn.lpstrFile = tszPath;	// tszPath���Z�b�g.
				ofn.nMaxFile = _MAX_PATH;	// _MAX_PATH���Z�b�g.
				ofn.Flags = OFN_OVERWRITEPROMPT;	// ���Ƀt�@�C�������鎞, �㏑�����邩�̊m�F��\��.
				// "���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.
				BOOL bRet = GetSaveFileName(&ofn);	// GetSaveFileName�Ńt�@�C���_�C�A���O��\����, �I�����ꂽ�t�@�C�������擾����.(�߂�l��bRet�Ɋi�[.)
				if (bRet){	// ����ɑI�����ꂽ.
					
					// �Z�[�u.
					m_pPicture->SaveImage(tszPath);	// m_pPicture->SaveImage�ŃZ�[�u.
					
				}

			}
		
			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ����ȊO.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

	}

	// TRUE.
	return TRUE;	// TRUE��Ԃ�.

}
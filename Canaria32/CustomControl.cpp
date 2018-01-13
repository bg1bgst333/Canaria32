// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl

// static�����o�ϐ��̒�`
std::map<tstring, WNDPROC>	CCustomControl::m_mapBaseWindowProcMap;	// �x�[�X�E�B���h�E�v���V�[�W���}�b�vm_mapBaseWindowProcMap

// �X�^�e�B�b�N�E�B���h�E�v���V�[�W��StaticWindowProc.
LRESULT CALLBACK CCustomControl::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// �|�C���^�̏�����
	CWindow *pWindow = NULL;	// CWindow�I�u�W�F�N�g�|�C���^pWindow��NULL�ɏ�����.

	// hwnd��CWindow�I�u�W�F�N�g�|�C���^����������, pWindow�Ɋi�[.
	if (m_mapWindowMap.find(hwnd) != m_mapWindowMap.end()){	// find�ŃL�[��hwnd�Ƃ���CWindow�I�u�W�F�N�g�|�C���^������������.
		pWindow = m_mapWindowMap[hwnd];	// pWindow��hwnd�ň�����CWindow�I�u�W�F�N�g�|�C���^���i�[.
	}

	// �E�B���h�E�I�u�W�F�N�g���擾�ł��Ȃ��ꍇ.
	if (pWindow == NULL){	// pWindow��NULL�̎�.

		// �z��̏�����
		TCHAR tszClassName[256] = {0};	// tszClassName��0�ŏ�����.

		// �E�B���h�E�n���h������E�B���h�E�N���X�����擾.
		GetClassName(hwnd, tszClassName, 256);	// GetClassName�ŃE�B���h�E�N���X�����擾.

		// tszClassName��m_mapBaseWindowProcMap�̃L�[�ɂ����.
		if (m_mapBaseWindowProcMap.find(tszClassName) != m_mapBaseWindowProcMap.end()){	// �݂�������.

			// ����̃v���V�[�W���ɔC����.
			return CallWindowProc(m_mapBaseWindowProcMap[tszClassName], hwnd, uMsg, wParam, lParam);	// CallWindowProc��, ���̃��b�Z�[�W��m_mapBaseWindowProcMap[tszClassName]�ɔC����.

		}
		else{	// �����ꍇ.

			// �����łȂ��Ȃ�, DefWindowProc�ɔC����.
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProc�̒l��Ԃ�.

		}

	}
	else{	// pWindow���������ꍇ.

		// ���̃E�B���h�E��DynamicWindowProc�ɔC����.
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);	// pWindow->DynamicWindowProc�ɓn��.

	}

}

// �E�B���h�E�쐬�֐�Create.
BOOL CCustomControl::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̈ʒu�E�T�C�Y���Z�b�g.
	m_x = x;				// m_x��x����.
	m_y = y;				// m_y��y����.
	m_iWidth = iWidth;		// m_iWidth��iWidth����.
	m_iHeight = iHeight;	// m_iHeight = iHeight����.

	// �E�B���h�E�̍쐬
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, this);	// CreateWindow�ŃE�B���h�E���쐬��, �n���h����m_hWnd�Ɋi�[.(�Ō�̈�����this��n��.)
	if (m_hWnd == NULL){	// m_hWnd��NULL�Ȃ玸�s.

		// ���s�Ȃ�FALSE
		return FALSE;	// FALSE��Ԃ�.

	}

	// GetWindowRect�Ő������RECT���擾��, ���߂ăT�C�Y���Z�b�g.
	RECT rc = {0};	// rc��{0}�ŏ�����.
	GetWindowRect(m_hWnd, &rc);	// GetWindowRect��rc���擾.
	m_x = rc.left;	// m_x��rc.left���Z�b�g.
	m_y = rc.top;	// m_y��rc.top���Z�b�g.
	m_iWidth = rc.right - rc.left;	// m_iWidth��rc.right - rc.left���Z�b�g.
	m_iHeight = rc.bottom - rc.top;	// m_iHeight��rc.bottom - rc.top���Z�b�g.

	// OnCreate�͈ȍ~�͌Ă΂�Ȃ��̂�, �����ŌĂ�ł���.
	CREATESTRUCT cs;	// CREATESTRUCT���ꉞ�p��.
	cs.hInstance = hInstance;	// hInstance�͗v�邩������Ȃ��̂�, ����͓n����悤�ɂ��Ă���.
	if (OnCreate(m_hWnd, &cs) != 0){	// OnCreate��m_hWnd��cs��n��.

		// �߂�l��0�łȂ���Ύ��s�Ȃ̂�, �E�B���h�E��j������.
		DestroyWindow(m_hWnd);	// DestroyWindow��m_hWnd��j��.
		m_hWnd = NULL;	// m_hWnd��NULL���Z�b�g.
		return FALSE;	// FALSE��Ԃ�.

	}

	// ����̃E�B���h�E�v���V�[�W�����擾��, CCustomControl::StaticWindowProc�ɍ����ւ���.
	WNDPROC lpfnWndProc;	// ����̃v���V�[�W��lpfnWndProc
	lpfnWndProc = (WNDPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);	// GetWindowLong�Ńv���V�[�W��lpfnWndProc���擾.
	SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)StaticWindowProc);	// SetWindowLong�Ńv���V�[�W��CCustomControl::StaticWindowProc��ݒ�.

	// �}�b�v�̃L�[�ɃE�B���h�E�N���X�����Ȃ���Γo�^.
	if (m_mapBaseWindowProcMap.find(lpctszClassName) == m_mapBaseWindowProcMap.end()){	// �}�b�v�ɖ�����.
		m_mapBaseWindowProcMap.insert(std::pair<tstring, WNDPROC>(lpctszClassName, lpfnWndProc));	// �v���V�[�W����o�^.
	}

	// WM_CREATE��ʂ�Ȃ��̂�, �E�B���h�E�}�b�v�̓o�^���s��.
	if (m_mapWindowMap.find(m_hWnd) == m_mapWindowMap.end()){	// �E�B���h�E�}�b�v�ɂȂ����.
		m_mapWindowMap.insert(std::pair<HWND, CWindow *>(m_hWnd, this));	// �o�^����.
	}

	// �����Ȃ�TRUE.
	return TRUE;	// TRUE��Ԃ�.

}

// �_�C�i�~�b�N�E�B���h�E�v���V�[�W��DynamicWindowProc.
LRESULT CCustomControl::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// �E�B���h�E���b�Z�[�W�̏���
	switch (uMsg){	// uMsg�̒l���Ƃɏ�����U�蕪����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

				// OnDestroy�ɔC����.
				OnDestroy();	// OnDestroy���Ă�.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		case WM_SIZE:

			// WM_SIZE�u���b�N
			{

				// �ϐ��̏�����
				UINT nType = (UINT)wParam;	// UINT�^nType��wParam���Z�b�g.
				int cx = LOWORD(lParam);	// int�^cx��LOWORD(lParam)���Z�b�g.
				int cy = HIWORD(lParam);	// int�^cy��HIWORD(lParam)���Z�b�g.

				// OnSize�ɔC����.
				OnSize(nType, cx, cy);	// OnSize��hwnd, nType, cx, cy��n��.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// ��ʂ̕`���v�����ꂽ��.
		case WM_PAINT:

			// WM_PAINT�u���b�N
			{

				// OnPaint�ɔC����.
				OnPaint();	// OnPaint���Ă�.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// �����̃��b�Z�[�W��DefWindowProc�ɓ����Ȃ���, ���������삵�Ȃ�.
		case WM_NCHITTEST:
		case WM_NCLBUTTONDOWN:
		case WM_NCLBUTTONUP:

			// DefWindowProc�ɔC����.
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// ������DefWindowProc�ɓn��, �߂�l�����̂܂ܕԂ�.

		// ���������̃X�N���[��������������.
		case WM_HSCROLL:

			// WM_HSCROLL�u���b�N
			{
				
				// OnHScroll�ɔC����.
				OnHScroll(LOWORD(wParam), HIWORD(wParam));	// OnHScroll�ɔC����.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// ���������̃X�N���[��������������.
		case WM_VSCROLL:

			// WM_VSCROLL�u���b�N
			{

				// OnVScroll�ɔC����.
				OnVScroll(LOWORD(wParam), HIWORD(wParam));	// OnVScroll�ɔC����.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// �}�E�X�̈ړ���.
		case WM_MOUSEMOVE:

			// WM_MOUSEMOVE�u���b�N
			{

				// �ϐ��̐錾
				POINT pt;	// POINT�\���̕ϐ�pt.

				// ���W�̎��o��.
				pt.x = LOWORD(lParam);	// lParam�̉��ʃ��[�h�����Wx.
				pt.y = HIWORD(lParam);	// lParam�̏�ʃ��[�h�����Wy.

				// OnMouseMove�ɔC����.
				OnMouseMove(wParam, pt);	// OnMouseMove��wParam��pt��n��.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// �}�E�X�̍��{�^���������ꂽ��.
		case WM_LBUTTONDOWN:

			// WM_LBUTTONDOWN�u���b�N
			{

				// �ϐ��̐錾
				POINT pt;	// POINT�\���̕ϐ�pt.

				// ���W�̎��o��.
				pt.x = LOWORD(lParam);	// lParam�̉��ʃ��[�h�����Wx.
				pt.y = HIWORD(lParam);	// lParam�̏�ʃ��[�h�����Wy.

				// OnLButtonDown�ɔC����.
				OnLButtonDown(wParam, pt);	// OnLButtonDown��wParam��pt��n��.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// �}�E�X�̍��{�^���������ꂽ�Ƃ�.
		case WM_LBUTTONUP:

			// WM_LBUTTONUP�u���b�N
			{

				// �ϐ��̐錾
				POINT pt;	// POINT�\���̕ϐ�pt.

				// ���W�̎��o��.
				pt.x = LOWORD(lParam);	// lParam�̉��ʃ��[�h�����Wx.
				pt.y = HIWORD(lParam);	// lParam�̏�ʃ��[�h�����Wy.

				// OnLButtonUp�ɔC����.
				OnLButtonUp(wParam, pt);	// OnLButtonUp��wParam��pt��n��.

			}
			
			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

		// ����ȊO�̎�.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏����֌�����.

	}

	// �z��̏�����
	TCHAR tszClassName[256] = {0};	// tszClassName��0�ŏ�����.

	// �E�B���h�E�n���h������E�B���h�E�N���X�����擾.
	GetClassName(hwnd, tszClassName, 256);	// GetClassName�ŃE�B���h�E�N���X�����擾.

	// tszClassName��m_mapBaseWindowProcMap�̃L�[�ɂ����.
	if (m_mapBaseWindowProcMap.find(tszClassName) != m_mapBaseWindowProcMap.end()){	// �݂�������.

		// ����̃v���V�[�W���ɔC����.
		return CallWindowProc(m_mapBaseWindowProcMap[tszClassName], hwnd, uMsg, wParam, lParam);	// CallWindowProc��, ���̃��b�Z�[�W��m_mapBaseWindowProcMap[tszClassName]�ɔC����.

	}
	else{	// �����ꍇ.

		// �����łȂ��Ȃ�, DefWindowProc�ɔC����.
		return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProc�̒l��Ԃ�.

	}

}

// �E�B���h�E���j�����ꂽ��.
void CCustomControl::OnDestroy(){

	// �����̃E�B���h�E�n���h�����c���Ă�����}�b�v����폜.
	if (m_mapWindowMap.find(m_hWnd) != m_mapWindowMap.end()){	// find�ł݂�������.
		m_mapWindowMap.erase(m_hWnd);	// m_mapWindowMap.erase�ō폜.
	}

}

// ��ʂ̕`���v�����ꂽ��.
void CCustomControl::OnPaint(){

}

// ���������X�N���[���o�[�̃C�x���g������������.
void CCustomControl::OnHScroll(UINT nSBCode, UINT nPos){

}

// ���������X�N���[���o�[�̃C�x���g������������.
void CCustomControl::OnVScroll(UINT nSBCode, UINT nPos){

}

// �}�E�X���ړ����Ă��鎞.
void CCustomControl::OnMouseMove(UINT nFlags, POINT pt){

}

// �}�E�X�̍��{�^���������ꂽ��.
void CCustomControl::OnLButtonDown(UINT nFlags, POINT pt){

}

// �}�E�X�̍��{�^���������ꂽ��.
void CCustomControl::OnLButtonUp(UINT nFlags, POINT pt){

}
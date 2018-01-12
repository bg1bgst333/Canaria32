// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <locale.h>	// ���P�[��
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// ���\�[�X

// static�����o�ϐ��̐錾
WNDPROC CMainWindow::m_lpfnWndProc = NULL;	// NULL�ŏ�����.

// static�ϐ��̐錾
static CMainWindow *pMainWnd = NULL;	// static��CMainWindow�I�u�W�F�N�g�|�C���^pMainWnd��NULL�ŏ�����.

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// �����o�̏�����.
	m_hPicture = NULL;	// m_hPicture��NULL�ŏ�����.
	m_iWidth = 0;	// m_iWidth��0�ŏ�����.
	m_iHeight = 0;	// m_iHeight��0�ŏ�����.
	m_hBitmap = NULL;	// m_hBitmap��NULL�ŏ�����.
	m_hMemDC = NULL;	// m_hMemDC��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������.
	if (m_hPicture != NULL){	// m_hPicture��NULL�łȂ���.
		DestroyWindow(m_hPicture);	// DestroyWindow��m_hPicture��j��.
		m_hPicture = NULL;	// m_hPicture��NULL���Z�b�g.
	}
	m_iWidth = 0;	// m_iWidth��0�ŏ�����.
	m_iHeight = 0;	// m_iHeight��0�ŏ�����.
	if (m_hBitmap != NULL){	// m_hBitmap��NULL�łȂ���.
		DeleteObject(m_hBitmap);	// DeleteObject��m_hBitmap��j��.
		m_hBitmap = NULL;	// m_hBitmap��NULL���Z�b�g.
	}
	if (m_hMemDC != NULL){	// m_hMemDC��NULL�łȂ���.
		DeleteDC(m_hMemDC);	// DeleteDC��m_hMemDC��j��.
		m_hMemDC = NULL;	// m_hMemDC��NULL���Z�b�g.
	}

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��IDR_MENU1���g��.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClass�œo�^.

}

// �X�^�e�B�b�N�E�B���h�E�v���V�[�W��PictureProc.(�s�N�`���[�R���g���[���̃v���V�[�W�������ւ���.)
LRESULT CALLBACK CMainWindow::PictureProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// static�ϐ��̐錾.
	static SCROLLINFO scrollInfo = {0};	// �X�N���[�����\����scrollInfo��{0}�ŏ�����.
	//static HDC hMemDC = NULL;	// �������f�o�C�X�R���e�L�X�g�n���h��hMemDC��NULL�ŏ�����.
	//static HBITMAP hBitmap = NULL;	// �r�b�g�}�b�v�n���h��hBitmap��NULL�ŏ�����.
	//static BITMAP bitmap = {0};	// BITMAP�\���̃I�u�W�F�N�gbitmap��{0}�ŏ�����.
	//static CMainWindow *pMainWnd = NULL;	// CMainWindow�I�u�W�F�N�g�|�C���^pMainWnd��NULL�ŏ�����.
	static int iHScrollPos = 0;	// iHScrollPos��0�ŏ�����.
	static int iVScrollPos = 0;	// iVScrollPos��0�ŏ�����.

	// �E�B���h�E���b�Z�[�W����
	switch (uMsg) {

		// �E�B���h�E�̍쐬���J�n���ꂽ��.
		case WM_CREATE:

			// WM_CREATE�u���b�N
			{
				// �ϐ��̐錾
				LPCREATESTRUCT lpCS;	// CreateStruct�\���̃|�C���^lpCS.

				// lpCS�̎擾.
				lpCS = (LPCREATESTRUCT)lParam;	// lParam��LPCREATESTRUCT�ɃL���X�g����, lpCS�Ɋi�[.

				// pMainWnd�Ƀ|�C���^���i�[.
				pMainWnd = (CMainWindow *)lpCS->lpCreateParams;	// lpCS->lpCreateParams��(CMainWindow *)�ɃL���X�g����pMainWnd�Ɋi�[.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

				// �������f�o�C�X�R���e�L�X�g�̔j��.
				if (pMainWnd->m_hMemDC != NULL){	// pMainWnd->m_hMemDC��NULL�łȂ����.
					// �폜.
					DeleteDC(pMainWnd->m_hMemDC);	// DeleteDC��pMainWnd->m_hMemDC�����.
					pMainWnd->m_hMemDC = NULL;	// pMainWnd->m_hMemDC��NULL���Z�b�g.
				}
				// �r�b�g�}�b�v���c���Ă�����폜.
				if (pMainWnd->m_hBitmap != NULL){	//pMainWnd->m_hBitmap��NULL�łȂ�.
					// �폜.
					DeleteObject(pMainWnd->m_hBitmap);	// DeleteObject��pMainWnd->m_hBitmap���폜.
					pMainWnd->m_hBitmap = NULL;	// pMainWnd->m_hBitmap��NULL���Z�b�g.
				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ��ʂ̕`���v�����ꂽ��.
		case WM_PAINT:

			// WM_PAINT�u���b�N
			{

				// �ϐ��̏�����.
				HDC hDC = NULL;	// hDC��NULL�ŏ�����.
				PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
				HBITMAP hOld = NULL;	// hOld��NULL�ŏ�����.
				int iDrawWidth;	// ���ۂ̕`�敝.
				int iDrawHeight;	// ���ۂ̕`�捂��.

				// �`��J�n.
				hDC = BeginPaint(hwnd, &ps);	// BeginPaint�ŕ`��J�n.

				// �r�b�g�}�b�v�̑I��.
				hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObject��hMemDC��pMainWnd->m_hBitmap��I��.
				
				// �r�b�g�]��.
				iDrawWidth = pMainWnd->m_iWidth - SCROLLBAR_THICKNESS;	// �`�敝 = �s�N�`���[�R���g���[���� - �X�N���[���o�[��.
				iDrawHeight = pMainWnd->m_iHeight - SCROLLBAR_THICKNESS;	// �`�捂�� = �s�N�`���[�R���g���[������ - �X�N���[���o�[����.
				BitBlt(hDC, 0, 0, iDrawWidth, iDrawHeight, pMainWnd->m_hMemDC, iHScrollPos, iVScrollPos, SRCCOPY);	// BitBlt��hMemDC��hDC�ɓ]��.

				// �Â��r�b�g�}�b�v���đI�����Ė߂�.
				SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObject��hOld��I��.

				// �X�N���[���o�[�ݒ�.
				// ��������.
				ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��scrollInfo���N���A.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
				scrollInfo.nPage = iDrawWidth;	// �`�敝
				scrollInfo.nMin = 0;	// �ŏ��l
				scrollInfo.nMax = pMainWnd->m_Bitmap.bmWidth;	//�ő�l
				SetScrollInfo(hwnd, SB_HORZ, &scrollInfo, FALSE);	// SetScrollInfo�ŃZ�b�g.
				// ��������.
				ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��scrollInfo���N���A.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
				scrollInfo.nPage = iDrawHeight;	// �`�捂��
				scrollInfo.nMin = 0;	// �ŏ��l
				scrollInfo.nMax =  pMainWnd->m_Bitmap.bmHeight;	//�ő�l
				SetScrollInfo(hwnd, SB_VERT, &scrollInfo, FALSE);	// SetScrollInfo�ŃZ�b�g.

				// �`��I��.
				EndPaint(hwnd, &ps);	// EndPaint�ŕ`��I��.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �����̃��b�Z�[�W��DefWindowProc�ɓ����Ȃ���, �X�N���[���o�[���F���������삵�Ȃ�.
		case WM_NCHITTEST:
		case WM_NCLBUTTONDOWN:
		case WM_NCLBUTTONUP:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// DefWindowProc�̒l��Ԃ�.

		// ���������̃X�N���[��������������.
		case WM_HSCROLL:

			// WM_HSCROLL�u���b�N
			{

				// �X�N���[�����擾.
				UINT nSBCode = LOWORD(wParam);	// LOWORD(wParam)�ŃX�N���[������̎�ނ��擾.
				UINT nPos = HIWORD(wParam);	// HIWORD(wParam)�ŃX�N���[���o�[�̈ʒu���擾.
				scrollInfo.fMask = SIF_POS;	// �ʒu�̂ݕύX.
				GetScrollInfo(hwnd, SB_HORZ, &scrollInfo);	// GetScrollInfo�ňʒu���̎擾.

				// �X�N���[���o�[����.
				switch (nSBCode){	// nSBCode�̒l�ŏ�����U�蕪����.

					// ��ԍ�
					case SB_LEFT:

						// SB_LEFT�u���b�N
						{

							// �ʒu���ŏ��l��.
							scrollInfo.nPos = scrollInfo.nMin;	// nMin���Z�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// ��ԉE
					case SB_RIGHT:

						// SB_RIGHT�u���b�N
						{

							// �ʒu���ő�l��.
							scrollInfo.nPos = scrollInfo.nMax;	// nMax���Z�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1��
					case SB_LINELEFT:

						// SB_LINELEFT�u���b�N
						{

							// nPos��0�łȂ���΃f�N�������g.
							if (scrollInfo.nPos > 0){
								scrollInfo.nPos--;	// nPos���f�N�������g.
							}

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1��E
					case SB_LINERIGHT:

						// SB_LINERIGHT�u���b�N
						{

							// nPos���ő�l-1�łȂ���΃C���N�������g.
							if (scrollInfo.nPos < scrollInfo.nMax - 1){
								scrollInfo.nPos++;	// nPos���C���N�������g.
							}

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1�y�[�W��
					case SB_PAGELEFT:

						// SB_PAGELEFT�u���b�N
						{

							// nPage�����炷.
							scrollInfo.nPos -= scrollInfo.nPage;	// nPos����nPage������.

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1�y�[�W�E
					case SB_PAGERIGHT:

						// SB_PAGERIGHT�u���b�N
						{

							// nPage�����₷.
							scrollInfo.nPos += scrollInfo.nPage;	// nPos����nPage������.

						}

						// ������.
						break;	// break�Ŕ�����.

					// �܂݂��h���b�O��.
					case SB_THUMBTRACK:

						// SB_THUMBTRACK�u���b�N
						{

							// ������nPos���Z�b�g.
							scrollInfo.nPos = nPos;	// ������nPos��scrollInfo.nPos�ɃZ�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// �܂݂��h���b�O��.
					case SB_THUMBPOSITION:

						// SB_THUMBPOSITION�u���b�N
						{

							// ������nPos���Z�b�g.
							scrollInfo.nPos = nPos;	// ������nPos��scrollInfo.nPos�ɃZ�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// ����ȊO.
					default:

						// ������.
						break;	// break�Ŕ�����.

				};

				// �X�N���[�����ݒ�.
				SetScrollInfo(hwnd, SB_HORZ, &scrollInfo, TRUE);	// SetScrollInfo�ŃX�N���[�������Z�b�g.
				// �����ʒu�̃Z�b�g.
				iHScrollPos = scrollInfo.nPos;	// iHScrollPos��scrollInfo.nPos���Z�b�g.
				// �����̈���쐬���ĉ�ʂ̍X�V.
				InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRect�ōX�V.
				// ���X�̃s�N�`���[�R���g���[���̃E�B���h�E�v���V�[�W���ɔC����.
				//return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProc��lpfnWndProc�ɔC����.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ���������X�N���[���o�[�̃C�x���g������������.
		case WM_VSCROLL:

			// WM_VSCROLL�u���b�N
			{

				// �X�N���[�����擾.
				UINT nSBCode = LOWORD(wParam);	// LOWORD(wParam)�ŃX�N���[������̎�ނ��擾.
				UINT nPos = HIWORD(wParam);	// HIWORD(wParam)�ŃX�N���[���o�[�̈ʒu���擾.
				scrollInfo.fMask = SIF_POS;	// �ʒu�̂ݕύX.
				GetScrollInfo(hwnd, SB_VERT, &scrollInfo);	// GetScrollInfo�ňʒu���̎擾.

				// �X�N���[���o�[����.
				switch (nSBCode){	// nSBCode�̒l�ŏ�����U�蕪����.

					// ��ԏ�
					case SB_TOP:

						// SB_TOP�u���b�N
						{

							// �ʒu���ŏ��l��.
							scrollInfo.nPos = scrollInfo.nMin;	// nMin���Z�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// ��ԉ�
					case SB_BOTTOM:

						// SB_BOTTOM�u���b�N
						{

							// �ʒu���ő�l��.
							scrollInfo.nPos = scrollInfo.nMax;	// nMax���Z�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1���
					case SB_LINEUP:

						// SB_LINEUP�u���b�N
						{

							// nPos��0�łȂ���΃f�N�������g.
							if (scrollInfo.nPos > 0){
								scrollInfo.nPos--;	// nPos���f�N�������g.
							}

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1��
					case SB_LINEDOWN:

						// SB_LINEDOWN�u���b�N
						{

							// nPos���ő�l-1�łȂ���΃C���N�������g.
							if (scrollInfo.nPos < scrollInfo.nMax - 1){
								scrollInfo.nPos++;	// nPos���C���N�������g.
							}

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1�y�[�W��
					case SB_PAGEUP:

						// SB_PAGEUP�u���b�N
						{

							// nPage�����炷.
							scrollInfo.nPos -= scrollInfo.nPage;	// nPos����nPage������.

						}

						// ������.
						break;	// break�Ŕ�����.

					// 1�y�[�W��
					case SB_PAGEDOWN:

						// SB_PAGEDOWN�u���b�N
						{

							// nPage�����₷.
							scrollInfo.nPos += scrollInfo.nPage;	// nPos����nPage������.

						}

						// ������.
						break;	// break�Ŕ�����.

					// �܂݂��h���b�O��.
					case SB_THUMBTRACK:

						// SB_THUMBTRACK�u���b�N
						{

							// ������nPos���Z�b�g.
							scrollInfo.nPos = nPos;	// ������nPos��scrollInfo.nPos�ɃZ�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// �܂݂��h���b�O��.
					case SB_THUMBPOSITION:

						// SB_THUMBPOSITION�u���b�N
						{

							// ������nPos���Z�b�g.
							scrollInfo.nPos = nPos;	// ������nPos��scrollInfo.nPos�ɃZ�b�g.

						}

						// ������.
						break;	// break�Ŕ�����.

					// ����ȊO.
					default:

						// ������.
						break;	// break�Ŕ�����.

				};

				// �X�N���[�����ݒ�.
				SetScrollInfo(hwnd, SB_VERT, &scrollInfo, TRUE);	// SetScrollInfo�ŃX�N���[�������Z�b�g.
				// �����ʒu�̃Z�b�g.
				iVScrollPos = scrollInfo.nPos;	// iVScrollPos��scrollInfo.nPos���Z�b�g.
				// �����̈���쐬���ĉ�ʂ̍X�V.
				InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRect�ōX�V.
				// ���X�̃s�N�`���[�R���g���[���̃E�B���h�E�v���V�[�W���ɔC����.
				//return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProc��lpfnWndProc�ɔC����.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �}�E�X���ړ����Ă��鎞.
		case WM_MOUSEMOVE:

			// WM_MOUSEMOVE�u���b�N
			{

				// ���W�̎擾.
				int x = LOWORD(lParam);	// LOWORD(lParam)��x���W.
				int y = HIWORD(lParam);	// HIWORD(lParam)��y���W.

				// �}�E�X�_�E���t���O�������Ă��鎞.
				if (wParam == MK_LBUTTON){	// ���{�^����������Ă��鎞.

					// �r�b�g�}�b�v�̑I��.
					HBITMAP hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObject��pMainWnd->m_hBitmap��I��.

					// �����ꂽ�ꏊ�ɍ����_���Z�b�g.
					SetPixel(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixel�ō����_���Z�b�g.

					// �O��̏ꏊ���牟���ꂽ�ꏊ�܂ł̒�����`��.
					LineTo(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos);	// LineTo�ŉ����ꂽ�ꏊ�܂ł̒�����`��.

					// �����ꂽ�ꏊ�Ɏn�_���ړ�.
					MoveToEx(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, NULL);	// MoveToEx�Ŏn�_���ړ�.

					// �Â��r�b�g�}�b�v���đI��.
					SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObject��hOld��I��.

					// ��ʍX�V.
					InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRect�ŉ�ʍX�V.

				}
				else{	// �}�E�X�_�E���t���O�������Ă��Ȃ���.

					// �}�E�X�̈ړ��ꏊ�Ɏn�_���ړ�.
					MoveToEx(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, NULL);	// MoveToEx�Ŏn�_���ړ�.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �}�E�X�̍��{�^���������ꂽ��.
		case WM_LBUTTONDOWN:

			// WM_LBUTTONDOWN�u���b�N
			{

				// ���W�̎擾.
				int x = LOWORD(lParam);	// LOWORD(lParam)��x���W.	
				int y = HIWORD(lParam);	// HIWORD(lParam)��y���W.

				// �}�E�X�_�E���t���O�������Ă��鎞.
				if (wParam == MK_LBUTTON){	// ���{�^����������Ă��鎞.

					// �r�b�g�}�b�v�̑I��.
					HBITMAP hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObject��pMainWnd->m_hBitmap��I��.

					// �����ꂽ�ꏊ�ɍ����_���Z�b�g.
					SetPixel(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixel�ō����_���Z�b�g.

					// �Â��r�b�g�}�b�v���đI��.
					SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObject��hOld��I��.

					// ��ʍX�V.
					InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRect�ŉ�ʍX�V.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �}�E�X�̍��{�^���������ꂽ��.
		case WM_LBUTTONUP:

			// WM_LBUTTONUP�u���b�N
			{

				// ���W�̎擾.
				int x = LOWORD(lParam);	// LOWORD(lParam)��x���W.
				int y = HIWORD(lParam);	// HIWORD(lParam)��y���W.

				// �}�E�X�_�E���t���O�������Ă��鎞.
				if (wParam == MK_LBUTTON){	// ���{�^����������Ă��鎞.

					// �r�b�g�}�b�v�̑I��.
					HBITMAP hOld = (HBITMAP)SelectObject(pMainWnd->m_hMemDC, pMainWnd->m_hBitmap);	// SelectObject��pMainWnd->m_hBitmap��I��.

					// �����ꂽ�ꏊ�ɍ����_���Z�b�g.
					SetPixel(pMainWnd->m_hMemDC, x + iHScrollPos, y + iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixel�ō����_���Z�b�g.

					// �Â��r�b�g�}�b�v���đI��.
					SelectObject(pMainWnd->m_hMemDC, hOld);	// SelectObject��hOld��I��.

					// ��ʍX�V.
					InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRect�ŉ�ʍX�V.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ��L�ȊO�̎�.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

	};

	// ����̃v���V�[�W���ɔC����.
	return CallWindowProc(m_lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProc�ł��̃��b�Z�[�W��m_mapBaseWindowProcMap[tszClassName]�ɔC����.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ���g�̃|�C���^��ۑ�.
	pMainWnd = this;	// pMainWnd��this���Z�b�g.

	// �s�N�`���[�R���g���[���̍쐬
	m_hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SS_BITMAP | SS_REALSIZECONTROL, 0, 0, m_iWidth, m_iHeight, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance, NULL);	// CreateWindow�Ńs�N�`���[�R���g���[��m_hPicture���쐬.(�E�B���h�E�N���X����"Static".SS_REALSIZECONTROL�Ȃ̂ŃR���g���[���T�C�Y�ɍ��킹�ĉ摜���g��k�������.)

	// �s�N�`���[�R���g���[������̃E�B���h�E�v���V�[�W�����擾��, PictureProc�ɍ����ւ���.
	m_lpfnWndProc = (WNDPROC)GetWindowLong(m_hPicture, GWL_WNDPROC);	// GetWindowLong�Ńv���V�[�W��m_lpfnWndProc���擾.
	SetWindowLong(m_hPicture, GWL_WNDPROC, (LONG)PictureProc);	// SetWindowLong��PictureProc���Z�b�g.

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

	// �s�N�`���[�̃T�C�Y�ύX.
	m_iWidth = cx;
	m_iHeight = cy;
	MoveWindow(m_hPicture, 0, 0, cx, cy, TRUE);	// MoveWindow��m_hPicture�̃T�C�Y���N���C�A���g�̈�Ɠ����ɂ���.

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

					// �E�B���h�E�T�C�Y�̃Z�b�g.
					RECT rc = {0};
					GetClientRect(pMainWnd->m_hWnd, &rc);
					pMainWnd->m_iWidth = rc.right;
					pMainWnd->m_iHeight = rc.bottom;

					// �r�b�g�}�b�v�����Ƀ��[�h�ς݂̏ꍇ.
					if (m_hBitmap != NULL){	// m_hBitmap��NULL�łȂ�.
						// ��U�폜.
						DeleteObject(m_hBitmap);	// DeleteObject��m_hBitmap���폜.
						m_hBitmap = NULL;	// m_hBitmap��NULL���Z�b�g.
					}

					// �r�b�g�}�b�v�̃��[�h.
					HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);	// GetWindowLong�ŃA�v���P�[�V�����C���X�^���X�n���h��hInstance���擾.
					m_hBitmap = (HBITMAP)LoadImage(hInstance, tszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// LoadImage�Ńr�b�g�}�b�v�����[�h.

					// �摜�̕��ƍ������擾.
					ZeroMemory(&m_Bitmap, sizeof(BITMAP));	// ZeroMemory��m_Bitmap��0�ŏ�����.
					GetObject(m_hBitmap, sizeof(BITMAP), &m_Bitmap);	// GetObject��m_hBitmap����BITMAP�\���̂��擾.
					
					// �f�o�C�X�R���e�L�X�g�n���h���̏�����.
					HDC hDC = NULL;	// hDC��NULL�ŏ�����.

					// �f�o�C�X�R���e�L�X�g�n���h���̎擾.
					hDC = GetDC(m_hPicture);	// GetDC��m_hPicture�̃f�o�C�X�R���e�L�X�ghDC���擾.

					// �������񃁃����f�o�C�X�R���e�L�X�g�̔j��.
					if (m_hMemDC != NULL){	// m_hMemDC��NULL�łȂ����.
						DeleteDC(m_hMemDC);	// DeleteDC��m_hMemDC�����.
						m_hMemDC = NULL;	// m_hMemDC��NULL���Z�b�g.
					}

					// �������f�o�C�X�R���e�L�X�g�̍쐬.
					m_hMemDC = CreateCompatibleDC(hDC);	// CreateCompatibleDC��hDC����m_hMemDC���쐬.

					// �r�b�g�}�b�v�̕\��.
					SendMessage(m_hPicture, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);	// SendMessage��STM_SETIMAGE�𑗂邱�Ƃ�m_hBitmap��\��.

					// �f�o�C�X�R���e�L�X�g�̉��.
					ReleaseDC(m_hPicture, hDC);	// ReleaseDC��hDC�����.

					// �����̈���쐬���ĉ�ʂ̍X�V.
					InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

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
					
					// �ϐ��̏�����.
					BITMAPINFO bi = {0};	// BITMAPINFO�\���̕ϐ�bi��{0}�ŏ�����.
					LPBYTE lpBitsPixel = NULL;	// LPBYTE�^(BYTE�^�|�C���^)��lpBitsPixel��NULL�ŏ�����.
					BITMAPFILEHEADER bfh = {0};	// BITMAPFILEHEADER�\����bfh��{0}�ŏ�����.
					HDC hDC = NULL;	// hDC��NULL�ŏ�����.
					FILE *fp = NULL;	// �t�@�C���|�C���^fp��NULL�ŏ�����.

					// �r�b�g�}�b�v���̃Z�b�g.
					bi.bmiHeader.biBitCount = 24;	// �ЂƂ܂�24bit�r�b�g�}�b�v�̂ݑΉ�.
					bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// BITMAPINFOHEADER�̃T�C�Y���w�肵�Ă���.
					bi.bmiHeader.biWidth = m_Bitmap.bmWidth;	// �摜��m_Bitmap.bmWidth���Z�b�g.
					bi.bmiHeader.biHeight = m_Bitmap.bmHeight;	// �摜����m_Bitmap.bmHeight���Z�b�g.
					bi.bmiHeader.biPlanes = 1;	// 1���Z�b�g.
					bi.bmiHeader.biCompression = BI_RGB;	// RGB.

					// DDB����DIB�̃s�N�Z������擾.
					hDC = GetDC(m_hPicture);	// GetDC��m_hPicture�̃f�o�C�X�R���e�L�X�ghDC���擾.
					GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, NULL, &bi, DIB_RGB_COLORS);	// GetDIBits�Ńs�N�Z����̃T�C�Y(bi.bmiHeader.biSizeImage)���擾.
					lpBitsPixel = new BYTE[bi.bmiHeader.biSizeImage];	// �s�N�Z����p�̃������m��.
					GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, lpBitsPixel, &bi, DIB_RGB_COLORS);	// GetDIBits�Ńs�N�Z������擾.
					ReleaseDC(m_hPicture, hDC);	// hDC�������[�X.

					// �r�b�g�}�b�v�t�@�C�����̃Z�b�g.(24bit�r�b�g�}�b�v�̏ꍇ.)
					bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	// �s�N�Z����ȊO�̃T�C�Y.(�܂�w�b�_�̃T�C�Y.)
					bfh.bfSize = bfh.bfOffBits + bi.bmiHeader.biSizeImage;	// �S�̂̃T�C�Y�̓w�b�_ + �s�N�Z����.
					bfh.bfType = 0x4d42;	// 0x4d42("BM")�̓r�b�g�}�b�v�ł���Ƃ����Ӗ�.
					bfh.bfReserved1 = 0;	// ������0���Z�b�g.
					bfh.bfReserved2 = 0;	// ������0���Z�b�g.

					// �t�@�C���̏�������.
					// ���{�ꃍ�P�[���̃Z�b�g.
					setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.
					// �t�@�C�������}���`�o�C�g�ɕϊ�.
					size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombs�Œ���filename_len�����߂�.(filename_len��NULL�����͊܂܂�Ȃ�.)
					char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// malloc�œ��I�z����m�ۂ�, �A�h���X��path�Ɋi�[.
					wcstombs(path, tszPath, _MAX_PATH);	// wcstombs��TCHAR����}���`�o�C�g�֕ϊ�.
					// �t�@�C�����J��.
					fp = fopen(path, "wb");	// �o�C�i�����[�h("wb")�ŊJ��.
					if (fp != NULL){	// fp��NULL�łȂ���.
						fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);	// fwrite��bfh����������.
						fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);	// fwrite��bi����������.
						fwrite(lpBitsPixel, sizeof(BYTE), bi.bmiHeader.biSizeImage, fp);	// fwrite��lpBitsPixel����������.
						fclose(fp);	// fclose��fp�����.
					}
					// �������̉��.
					free(path);	// free��path�����.
					delete[] lpBitsPixel;	// delete[]��lpBitsPixel�����.

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
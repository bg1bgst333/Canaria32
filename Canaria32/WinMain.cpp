// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI
// �Ǝ��̃w�b�_
#include "resource.h"	// ���\�[�X

// �}�N���̒�`
#define SCROLLBAR_THICKNESS 16	// �Ƃ肠�����X�N���[���o�[�̌����̓}�N����16�Ƃ��Ă���.

// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��WindowProc

// _tWinMain�֐��̒�`
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd){

	// �ϐ��E�\���̂̐錾
	HWND hWnd;		// HWND�^�E�B���h�E�n���h��hWnd
	MSG msg;		// MSG�^���b�Z�[�W�\����msg
	WNDCLASS wc;	// WNDCLASS�^�E�B���h�E�N���X�\����wc

	// �E�B���h�E�N���X�\����wc�Ƀp�����[�^���Z�b�g.
	wc.lpszClassName = _T("Canaria");	// �E�B���h�E�N���X���͂Ƃ肠����"Canaria"�Ƃ���.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// �X�^�C���͂Ƃ肠����CS_HREDRAW | CS_VREDRAW�ɂ���.
	wc.lpfnWndProc = WindowProc;	// �E�B���h�E�v���V�[�W���ɂ͉��Œ�`����WindowProc���w�肷��.
	wc.hInstance = hInstance;	// �A�v���P�[�V�����C���X�^���X�n���h���͈�����hInstance���g��.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// LoadIcon�ŃA�v���P�[�V��������̃A�C�R�������[�h.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// LoadCursor�ŃA�v���P�[�V��������̃J�[�\�������[�h.
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	// GetStockObject�Ń��C�g�O���[�u���V��w�i�F�Ƃ���.
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// MAKEINTRESOURCE�Ƀ��j���[�̃��\�[�XID(IDR_MENU1)���w�肵, wc.lpszMenuName�Ɋi�[.
	wc.cbClsExtra = 0;	// �Ƃ肠����0���w��.
	wc.cbWndExtra = 0;	// �Ƃ肠����0���w��.

	// �E�B���h�E�N���X�̓o�^
	if (!RegisterClass(&wc)){	// RegisterClass�ŃE�B���h�E�N���X��o�^����.

		// �߂�l��0�Ȃ�o�^���s�Ȃ̂ŃG���[����.
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!(-1)"), _T("Canaria"), MB_OK | MB_ICONHAND);	// MessageBox��"�\�����ʃG���[���������܂���!(-1)"�ƕ\��.
		return -1;	// return��-1��Ԃ��Ĉُ�I��.

	}

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(wc.lpszClassName, _T("Canaria"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);	// CreateWindow�ŃE�B���h�E�N���X����"Canaria"�ȃE�B���h�E"Canaria"���쐬.
	if (hWnd == NULL){	// hWnd��NULL�Ȃ�E�B���h�E�쐬���s.

		// �G���[����
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!(-2)"), _T("Canaria"), MB_OK | MB_ICONHAND);	// MessageBox��"�\�����ʃG���[���������܂���!(-2)"�ƕ\��.
		return -2;	// return��-2��Ԃ��Ĉُ�I��.

	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, SW_SHOW);	// ShowWindow�ŃE�B���h�E��\��.

	// ���b�Z�[�W���[�v�̏���
	while (GetMessage(&msg, NULL, 0, 0) > 0){	// GetMessage�ŃE�B���h�E���b�Z�[�W���擾��, msg�Ɋi�[.(0�ȉ��Ȃ�, �����𔲂���.)

		// ���b�Z�[�W�̕ϊ��Ƒ��o.
		TranslateMessage(&msg);	// TranslateMessage�ŉ��z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�.
		DispatchMessage(&msg);	// DispatchMessage�Ń��b�Z�[�W���E�B���h�E�v���V�[�W��WindowProc�ɑ��o.

	}

	// �v���O�����̏I��
	return (int)msg.wParam;	// �I���R�[�h(msg.wParam)��߂�l�Ƃ��ĕԂ�.

}

// �E�B���h�E�v���V�[�W��WindowProc�̒�`
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// �X�^�e�B�b�N�ϐ��̏�����.
	static HWND hPicture = NULL;	// �s�N�`���[�R���g���[���n���h��hPicture��NULL�ŏ�����.
	static HBITMAP hBitmap = NULL;	// �r�b�g�}�b�v�n���h��hBitmap��NULL�ŏ�����.
	static BITMAP bitmap = {0};	// BITMAP�\���̃I�u�W�F�N�gbitmap��{0}�ŏ�����.
	static HDC hMemDC = NULL;	// �������f�o�C�X�R���e�L�X�g�n���h��hMemDC��NULL�ŏ�����.
	static int iHScrollPos = 0;	// iHScrollPos��0�ŏ�����.
	static int iVScrollPos = 0;	// iVScrollPos��0�ŏ�����.
	static SCROLLINFO scrollInfo = {0};	// �X�N���[�����\����scrollInfo��{0}�ŏ�����.
	static WNDPROC lpfnWndProc = NULL;	// ����̃E�B���h�E�v���V�[�W��lpfnWndProc��NULL�ŏ�����.

	// �E�B���h�E���b�Z�[�W�̏���.
	switch (uMsg){	// uMsg�̒l���Ƃɏ�����U�蕪����.

		// �E�B���h�E�̍쐬���J�n���ꂽ��.
		case WM_CREATE:

			// WM_CREATE�u���b�N
			{

				// �ϐ��̐錾
				LPCREATESTRUCT lpCS;	// CreateStruct�\���̃|�C���^lpCS.

				// lpCS�̎擾.
				lpCS = (LPCREATESTRUCT)lParam;	// lParam��LPCREATESTRUCT�ɃL���X�g����, lpCS�Ɋi�[.

				// �s�N�`���[�R���g���[���̍쐬
				//hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_REALSIZEIMAGE, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindow�Ńs�N�`���[�R���g���[��hPicture���쐬.(�E�B���h�E�N���X����"Static".SS_REALSIZEIMAGE�Ȃ̂ŉ摜�T�C�Y�ɍ��킹�ăR���g���[���̃T�C�Y���ω�.)
				hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SS_BITMAP | SS_REALSIZECONTROL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindow�Ńs�N�`���[�R���g���[��hPicture���쐬.(�E�B���h�E�N���X����"Static".SS_REALSIZECONTROL�Ȃ̂ŃR���g���[���T�C�Y�ɍ��킹�ĉ摜���g��k�������.)

				// �s�N�`���[�R���g���[������̃E�B���h�E�v���V�[�W�����擾��, WindowProc�ɍ����ւ���.
				lpfnWndProc = (WNDPROC)GetWindowLong(hPicture, GWL_WNDPROC);	// GetWindowLong�Ńv���V�[�W��lpfnWndProc���擾.
				SetWindowLong(hPicture, GWL_WNDPROC, (LONG)WindowProc);	// SetWindowLong��WindowProc���Z�b�g.

				// �X�N���[���o�[�ݒ�.
				// ���������̐ݒ�.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y��sizeof(SCROLLINFO).
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �ݒ肷�鍀�ڂ̃t���O�̓y�[�W�ƃ����W.
				scrollInfo.nPage = 50;
				scrollInfo.nMin = 0;	// �ŏ��l��0.
				scrollInfo.nMax = 400;
				SetScrollInfo(hPicture, SB_HORZ, &scrollInfo, FALSE);	// SetScrollInfo��scrollInfo���Z�b�g.
				// ���������̐ݒ�.
				scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y��sizeof(SCROLLINFO).
				scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �ݒ肷�鍀�ڂ̃t���O�̓y�[�W�ƃ����W.
				scrollInfo.nPage = 50;
				scrollInfo.nMin = 0;	// �ŏ��l��0.
				scrollInfo.nMax = 400;
				SetScrollInfo(hPicture, SB_VERT, &scrollInfo, FALSE);	// SetScrollInfo��scrollInfo���Z�b�g.

				// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
				return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

				// �������f�o�C�X�R���e�L�X�g�̔j��.
				if (hMemDC != NULL){	// hMemDC��NULL�łȂ����.
					// �폜.
					DeleteDC(hMemDC);	// DeleteDC��hMemDC�����.
					hMemDC = NULL;	// hMemDC��NULL���Z�b�g.
				}
				// �r�b�g�}�b�v���c���Ă�����폜.
				if (hBitmap != NULL){	// hBitmap��NULL�łȂ�.
					// �폜.
					DeleteObject(hBitmap);	// DeleteObject��hBitmap���폜.
					hBitmap = NULL;	// hBitmap��NULL���Z�b�g.
				}

				// �I�����b�Z�[�W�̑��M.
				PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ��ʂ̕`���v�����ꂽ��.
		case WM_PAINT:

			// WM_PAINT�u���b�N
			{

				// hPicture�̎��͂�����ŕ`��.
				if (hwnd == hPicture){	// hwnd��hPicture��������.

					// �ϐ��̏�����.
					HDC hDC = NULL;	// hDC��NULL�ŏ�����.
					PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
					HBITMAP hOld = NULL;	// hOld��NULL�ŏ�����.
					int iDrawWidth;	// ���ۂ̕`�敝.
					int iDrawHeight;	// ���ۂ̕`�捂��.

					// �`��J�n.
					hDC = BeginPaint(hwnd, &ps);	// BeginPaint�ŕ`��J�n.

					// �r�b�g�}�b�v�̑I��.
					hOld = (HBITMAP)SelectObject(hMemDC, hBitmap);	// SelectObject��hMemDC��hBitmap��I��.
					
					// �r�b�g�]��.
					iDrawWidth = 640 - SCROLLBAR_THICKNESS;	// �`�敝 = �s�N�`���[�R���g���[���� - �X�N���[���o�[��.
					iDrawHeight = 480 - SCROLLBAR_THICKNESS;	// �`�捂�� = �s�N�`���[�R���g���[������ - �X�N���[���o�[����.
					BitBlt(hDC, 0, 0, iDrawWidth, iDrawHeight, hMemDC, iHScrollPos, iVScrollPos, SRCCOPY);	// BitBlt��hMemDC��hDC�ɓ]��.

					// �Â��r�b�g�}�b�v���đI�����Ė߂�.
					SelectObject(hMemDC, hOld);	// SelectObject��hOld��I��.

					// �X�N���[���o�[�ݒ�.
					// ��������.
					ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��scrollInfo���N���A.
					scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
					scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
					scrollInfo.nPage = iDrawWidth;	// �`�敝
					scrollInfo.nMin = 0;	// �ŏ��l
					scrollInfo.nMax = bitmap.bmWidth;	//�ő�l
					SetScrollInfo(hwnd, SB_HORZ, &scrollInfo, FALSE);	// SetScrollInfo�ŃZ�b�g.
					// ��������.
					ZeroMemory(&scrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��scrollInfo���N���A.
					scrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
					scrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
					scrollInfo.nPage = iDrawHeight;	// �`�捂��
					scrollInfo.nMin = 0;	// �ŏ��l
					scrollInfo.nMax = bitmap.bmHeight;	//�ő�l
					SetScrollInfo(hwnd, SB_VERT, &scrollInfo, FALSE);	// SetScrollInfo�ŃZ�b�g.

					// �`��I��.
					EndPaint(hwnd, &ps);	// EndPaint�ŕ`��I��.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �R�}���h������������.
		case WM_COMMAND:

			// WM_COMMAND�u���b�N
			{

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
							ofn.hwndOwner = hwnd;	// hwnd���Z�b�g.
							ofn.lpstrFilter = _T("�r�b�g�}�b�v�摜(*.bmp)\0*.bmp\0���ׂẴt�@�C��(*.*)\0*.*\0\0");	// �r�b�g�}�b�v�摜�Ƃ��ׂẴt�@�C���̃t�B���^���Z�b�g.
							ofn.lpstrFile = tszPath;	// tszPath���Z�b�g.
							ofn.nMaxFile = _MAX_PATH;	// _MAX_PATH���Z�b�g.
							ofn.Flags = OFN_FILEMUSTEXIST;	// �t�@�C�������݂��Ȃ��Ɣ������Ȃ�.
							// "�J��"�t�@�C���_�C�A���O�̕\��.
							BOOL bRet = GetOpenFileName(&ofn);	// GetOpenFileName�Ńt�@�C���_�C�A���O��\����, �I�����ꂽ�t�@�C�������擾����.(�߂�l��bRet�Ɋi�[.)
							if (bRet){	// ����ɑI�����ꂽ.

								// �r�b�g�}�b�v�����Ƀ��[�h�ς݂̏ꍇ.
								if (hBitmap != NULL){	// hBitmap��NULL�łȂ�.
									// ��U�폜.
									DeleteObject(hBitmap);	// DeleteObject��hBitmap���폜.
									hBitmap = NULL;	// hBitmap��NULL���Z�b�g.
								}

								// �r�b�g�}�b�v�̃��[�h.
								HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);	// GetWindowLong�ŃA�v���P�[�V�����C���X�^���X�n���h��hInstance���擾.
								hBitmap = (HBITMAP)LoadImage(hInstance, tszPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// LoadImage�Ńr�b�g�}�b�v�����[�h.

								// �摜�̕��ƍ������擾.
								ZeroMemory(&bitmap, sizeof(BITMAP));	// ZeroMemory��bitmap��0�ŏ�����.
								GetObject(hBitmap, sizeof(BITMAP), &bitmap);	// GetObject��hBitmap����BITMAP�\���̂��擾.
								
								// �f�o�C�X�R���e�L�X�g�n���h���̏�����.
								HDC hDC = NULL;	// hDC��NULL�ŏ�����.

								// �f�o�C�X�R���e�L�X�g�n���h���̎擾.
								hDC = GetDC(hPicture);	// GetDC��hPicture�̃f�o�C�X�R���e�L�X�ghDC���擾.

								// �������񃁃����f�o�C�X�R���e�L�X�g�̔j��.
								if (hMemDC != NULL){	// hMemDC��NULL�łȂ����.
									DeleteDC(hMemDC);	// DeleteDC��hMemDC�����.
									hMemDC = NULL;	// hMemDC��NULL���Z�b�g.
								}

								// �������f�o�C�X�R���e�L�X�g�̍쐬.
								hMemDC = CreateCompatibleDC(hDC);	// CreateCompatibleDC��hDC����hMemDC���쐬.

								// �r�b�g�}�b�v�̕\��.
								SendMessage(hPicture, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);	// SendMessage��STM_SETIMAGE�𑗂邱�Ƃ�hBitmap��\��.

								// �f�o�C�X�R���e�L�X�g�̉��.
								ReleaseDC(hPicture, hDC);	// ReleaseDC��hDC�����.

								// �����̈���쐬���ĉ�ʂ̍X�V.
								InvalidateRect(hwnd, NULL, TRUE);	// InvalidateRect�ōX�V.

							}

						}

						// ����̏����֌�����.
						break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

					// "���O��t���ĕۑ�(&A)..."
					case ID_FILE_SAVE_AS:

						// ID_FILE_SAVE_AS�u���b�N
						{

							// ���b�Z�[�W�{�b�N�X��"ID_FILE_SAVE_AS"�ƕ\��.
							MessageBox(NULL, _T("ID_FILE_SAVE_AS"), _T("Canaria"), MB_OK | MB_ICONASTERISK);	// MessageBox��"ID_FILE_SAVE_AS"�ƕ\��.

						}
					
						// ����̏����֌�����.
						break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

					// ����ȊO.
					default:

						// ����̏����֌�����.
						break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ���������̃X�N���[��������������.
		case WM_HSCROLL:

			// WM_HSCROLL�u���b�N
			{
				
				// hwnd��hPicture�̎���, �ŏI�I�ɂ͌��X�̃E�B���h�E�v���V�[�W���ɔC����.
				if (hwnd == hPicture){	// hwnd��hPicture��������.

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
					return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProc��lpfnWndProc�ɔC����.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ���������̃X�N���[��������������.
		case WM_VSCROLL:

			// WM_VSCROLL�u���b�N
			{
				
				// hwnd��hPicture�̎���, �ŏI�I�ɂ͌��X�̃E�B���h�E�v���V�[�W���ɔC����.
				if (hwnd == hPicture){	// hwnd��hPicture��������.

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
					return CallWindowProc(lpfnWndProc, hwnd, uMsg, wParam, lParam);	// CallWindowProc��lpfnWndProc�ɔC����.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ��L�ȊO�̎�.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

	}

	// ���Ƃ͊���̏����ɔC����.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// �߂�l���܂߂�DefWindowProc�Ɋ���̏�����C����.

}
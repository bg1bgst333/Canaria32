// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI
// �Ǝ��̃w�b�_
#include "resource.h"	// ���\�[�X

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
				hPicture = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_REALSIZECONTROL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindow�Ńs�N�`���[�R���g���[��hPicture���쐬.(�E�B���h�E�N���X����"Static".SS_REALSIZECONTROL�Ȃ̂ŃR���g���[���T�C�Y�ɍ��킹�ĉ摜���g��k�������.)

				// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
				return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

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

								// �r�b�g�}�b�v�̕\��.
								SendMessage(hPicture, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);	// SendMessage��STM_SETIMAGE�𑗂邱�Ƃ�hBitmap��\��.
							
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

		// ��L�ȊO�̎�.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

	}

	// ���Ƃ͊���̏����ɔC����.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// �߂�l���܂߂�DefWindowProc�Ɋ���̏�����C����.

}
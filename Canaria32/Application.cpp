// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Application.h"	// CApplication

// ���b�Z�[�W���[�v�����֐�Run.
int CApplication::Run(){

	// �\���̂̐錾.
	MSG msg;	// MSG�^���b�Z�[�W�\����msg

	// ���b�Z�[�W���[�v�̏���
	while (GetMessage(&msg, NULL, 0, 0) > 0){	// GetMessage�ŃE�B���h�E���b�Z�[�W���擾��, msg�Ɋi�[.(0�ȉ��Ȃ�, �����𔲂���.)

		// ���b�Z�[�W�̕ϊ��Ƒ��o.
		TranslateMessage(&msg);	// TranslateMessage�ŉ��z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�.
		DispatchMessage(&msg);	// DispatchMessage�Ń��b�Z�[�W���E�B���h�E�v���V�[�W��WindowProc�ɑ��o.

	}

	// ExitInstance�̒l��Ԃ�.
	return ExitInstance();	// return��ExitInstance��Ԃ�.

}

// �I�������֐�ExitInstance.
int CApplication::ExitInstance(){

	// ����͏��0��Ԃ�.
	return 0;	// return��0��Ԃ�.

}
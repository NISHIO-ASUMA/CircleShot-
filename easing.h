//=============================================
//
// �C�[�W���O���� [ easing.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _EASING_H_ // ���̃}�N����`������ĂȂ�������
#define _EASING_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �C�[�W���O�̃N���X��`
//*********************************
class CEasing
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEasing();
	~CEasing();

	// �ÓI�����o�֐�
	static float EaseInsine(float t);
	static float EaseOutsine(float t);

private:

};

#endif
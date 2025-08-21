//====================================
//
// �U���O�����o [ attacksign.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ATTACKSIGN_H_ // ���̃}�N����`������ĂȂ�������
#define _ATTACKSIGN_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2d.h"

//**********************
// �O���錾
//**********************
class CObject;

//**********************
// �U���O���N���X���`
//**********************
class CAttackSign : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CAttackSign(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CAttackSign();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CAttackSign* Create(float fWidth, float fHeight);

private:
	int m_nidxTex;		// �e�N�X�`���C���f�b�N�X
	int m_nLife;		// ����
};

#endif


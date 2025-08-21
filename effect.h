//====================================
//
// �G�t�F�N�g���� [ effect.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EFFECT_H_ // ���̃}�N����`������ĂȂ�������
#define _EFFECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"

//*************************************************
// �G�t�F�N�g�N���X���` ( �p�� : �r���{�[�h )
//*************************************************
class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffect();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife) { m_nLife = nLife; }

	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);
	void SetTexture(void);

	int GetLife(void) { return m_nLife; }

private:
	int m_nLife;						  // �̗�
	float m_fRadius;					  // ���a
	D3DXVECTOR3 m_move;					  // �ړ���
	int m_nIdxTexture;					  // �e�N�X�`���C���f�b�N�X
};

#endif

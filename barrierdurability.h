//============================================
//
// �V�[���h�ϋv�l�֐� [ barrierdurability.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _BARRIERDURABILITY_H_ // ���̃}�N����`������ĂȂ�������
#define _BARRIERDURABILITY_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "object2D.h"

//*********************************
// �O���錾
//*********************************
class CObject;

//*********************************
// �ϋv�l�N���X���`
//*********************************
class CBarrierDurability : public CObject2D
{
public:
	CBarrierDurability(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBarrierDurability();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(int nType);
	void SetCreateFlag(bool isFlags) { m_isCreate = isFlags;}

	static CBarrierDurability* Create(D3DXVECTOR3 pos, float fHeight, float fWidth, int nType);

private:
	int m_nIdxTex; // �e�N�X�`���C���f�b�N�X
	bool m_isCreate; // �����\���ǂ���
};


#endif
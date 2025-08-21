//====================================
//
// �������� [ explosion.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EXPLOSION_H_ // ���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************

#include "object2D.h"

//**************************
// �����N���X���`
//**************************
class CExplosion : public CObject2D
{
public:
	CExplosion(int nPriority = 3);
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,D3DXCOLOR col);

	void SetTexture();

private:
	int m_nIdxTexture;
};

#endif
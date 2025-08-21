//====================================
//
// �u���b�N���� [ block.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BLOCK_H_ // ���̃}�N����`������ĂȂ�������
#define _BLOCK_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"

//************************************
// �u���b�N�N���X���`
//************************************
class CBlock : public CObjectX
{
public:
	CBlock(int nPriority = static_cast<int>(CObject::PRIORITY::BLOCK));
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetSize(void) const { return m_size; }

	static CBlock* Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot, float fSize);

private:
	float m_size; // �T�C�Y�ݒ�p
};

#endif

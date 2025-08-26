//========================================
//
// ���I�I�u�W�F�N�g���� [ rubble.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _RUBBLE_H_ // ���̃}�N����`������ĂȂ�������
#define _RUBBLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "objectX.h"

//**********************************
// �O���錾
//**********************************
class CObject;

//**********************************
// ���I�N���X���`
//**********************************
class CRubble : public CObjectX
{
public:
	CRubble(int nPriority = static_cast<int>(CObject::PRIORITY::BLOCK));
	~CRubble();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:
	
};

#endif
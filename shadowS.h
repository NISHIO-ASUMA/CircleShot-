//====================================
//
// �X�e���V���V���h�E���� [ shadowS.h ]
// Author: Asuma Nishio
//
//=====================================
#ifndef _SHADOWS_H_ // ���̃}�N����`������ĂȂ�������
#define _SHADOWS_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"
#include "object.h"
#include "object2D.h"

//**********************************
// �V���h�E�X�e���V���N���X���`
//**********************************
class CShadowS :public CObjectX
{
public:
	CShadowS(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadowS();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowS* Create(const char * pFileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;

};

#endif

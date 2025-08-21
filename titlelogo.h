//=========================================
//
// �^�C�g�����S���� [ titlelogo.h ]
// Author: Asuma Nishio
// 
//==========================================

#ifndef _TITLELOGO_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLELOGO_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "object2D.h"

//***************************
// �O���錾
//***************************
class CObject;

//***************************
// �^�C�g�����S�N���X��`
//***************************
class CTitleLogo : public CObject2D
{
public:
	CTitleLogo(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleLogo();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	static CTitleLogo* Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nAnchorType);

private:
	int m_nTexIdx;		// �e�N�X�`���C���f�b�N�X

};

#endif

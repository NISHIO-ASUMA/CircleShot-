//============================================
//
// �Q�[�W�֌W�̃N���X���� [ gage.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _GAGE_H_ // ���̃}�N����`������ĂȂ�������
#define _GAGE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//**********************
// �Q�[�W�N���X���`
//**********************
class CGage :public CObject2D
{
public:

	CGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height);

	static CGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	int m_nTextIdx;	// �e�N�X�`�����ʔԍ�
};

#endif


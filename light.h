//====================================
//
// ���C�g���� [ light.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _LIGHT_H_ // ���̃}�N����`������ĂȂ�������
#define _LIGHT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// ���C�g�N���X���`
//**********************
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static inline constexpr int NUMLIGHT = 3;

private:
	D3DLIGHT9 m_aLight[NUMLIGHT]; // ���C�g��
	D3DXVECTOR3 m_vecDir[NUMLIGHT];	// �x�N�g��
};

#endif
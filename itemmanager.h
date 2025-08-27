//============================================
//
// �A�C�e���Ǘ����� [ itemmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _ITEMMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _ITEMMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �A�C�e���S�̂̊Ǘ��N���X���`
//*********************************
class CItemManager
{
public:
	CItemManager();
	~CItemManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	// ���W���X�g
	D3DXVECTOR3 m_ActivePointPos[3] =
	{
		{100.0f,50.0f,-550.0f},
		{100.0f,50.0f,550.0f},
		{0.0f,0.0f,0.0f},
	};
};

#endif

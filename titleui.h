//====================================
//
// �^�C�g��ui���� [ titleui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TITLEUI_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLEUI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//************************************
// �^�C�g��2D�I�u�W�F�N�g�N���X���`
//************************************
class CTitleUi : public CObject2D
{
public:
	//********************
	// ���j���[���ʗ񋓌^
	//********************
	enum MENU
	{
		MENU_GAME,
		MENU_TUTORIAL,
		MENU_MAX
	};

	CTitleUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleUi* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight,int nType);

	void SetTexture(int nType);

private:
	int m_nTexIdx; // �e�N�X�`���C���f�b�N�X
};

#endif
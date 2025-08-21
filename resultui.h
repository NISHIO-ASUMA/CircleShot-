//====================================
//
// ���U���gui�������� [ resultui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RESULTUI_H_ // ���̃}�N����`������ĂȂ�������
#define _RESULTUI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//****************************
// ���U���gUI�N���X���`
//****************************
class CResultUi : public CObject2D
{
public:

	//********************
	// �񋓌^
	//********************
	enum TYPE
	{
		TYPE_NONE,
		MENU_MAX
	};

	CResultUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultUi* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType);

	void SetTexture(int nType);

private:
	int m_nIdxTex;		// �e�N�X�`���C���f�b�N�X

};

#endif

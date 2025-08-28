//=============================================
//
// �`���[�g���A��UI���� [ tutorialui.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTORIALUI_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTORIALUI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "object2D.h"

//******************************
// �`���[�g���A��ui�N���X���`
//******************************
class CTutorialUi : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTutorialUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTutorialUi();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(int nType);

	// �ÓI�����o�֐�
	static CTutorialUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

private:
	int m_nIdxTexture;	// �e�N�X�`���C���f�b�N�X
};

#endif

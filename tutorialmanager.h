//=============================================
//
// �`���[�g���A���Ǘ����� [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTORIALMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTORIALMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �O���錾
//******************************
class CTutorialUi;

//******************************
// �}�l�[�W���[�Ǘ��N���X���`
//******************************
class CTutorialManager
{
public:
	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // �`���[�g���A��ui�N���X�̃|�C���^

};

#endif

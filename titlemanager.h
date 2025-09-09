//==========================================
//
// �^�C�g���Ǘ����� [ titlemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

#ifndef _TITLEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************
// �O���錾
//**************
class CTitleUi;
class CPointUi;

//**************************************
// �^�C�g���}�l�[�W���[�Ǘ��N���X���`
//**************************************
class CTitleManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleManager(bool isCreate = true);
	~CTitleManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	static constexpr int SELECT_START = 0;			// �I���J�n�ԍ�
	static constexpr int TITLE_MENU = 3;			// �^�C�g���I��ui��
	static constexpr int SELECT_END = 2;			// �ő�l

	static constexpr float UIWIDTH = 195.0f;		// ui�̉���
	static constexpr float UIHEIGHT = 50.0f;		// ui�̍���
	static constexpr float FIELDWIDTH = 1000.0f;	// �n�ʂ̍L��
	static constexpr float INTERVAL = 430.0f;		// �����̊Ԋu

	int m_nIdx;					// �I��ԍ�
	bool m_isuiCreate;			// �������ꂽ���ǂ����̔��ʃt���O
	bool m_isFirstuiCreate;		// �ŏ��̃V�[���Ő������ꂽ�����ʃt���O

	CTitleUi* m_pTitleui[TITLE_MENU]; // �N���X�|�C���^
	CPointUi* m_pPointUi;			  // �N���X�|�C���^
};

#endif


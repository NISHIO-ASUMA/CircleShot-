//====================================
//
// �G�f�B�^�[���� [ uiedit.h ]
// 
// TODO : ���I����Ȃ����ʂɔz��ł�肽��
// Author: Asuma Nishio
//
//=====================================

#ifndef _UIEDIT_H_ // ���̃}�N����`������ĂȂ�������
#define _UIEDIT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include <vector>

//******************************
// �O���錾
//******************************
class CUi;

//*******************************
// UI�G�f�B�^�[�N���X���`
//*******************************
class CUiedit
{
public:
	CUiedit();
	~CUiedit();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddUi(D3DXVECTOR3 pos, int type, float width, float height);
	void SaveFile(const char* filename);
	void ReloadFile(const char* filename);

	//**********************
	// �\���̒�`
	//**********************
	struct EditInfo
	{
		D3DXVECTOR3 pos;// ���W
		float fWidth;   // ����
		float fHeight;	// ����
		int nType;		// ���
		CUi* pUi; // UI�|�C���^
	};

	// �Q�b�^�[
	std::vector<EditInfo>& GetEditInfoList() { return m_pUi; }

private:
	std::vector<EditInfo> m_pUi; // ui���I�z��
};

#endif
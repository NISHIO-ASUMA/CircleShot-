//=================================================
//
// ���I�I�u�W�F�N�g�Ǘ����� [ rubblemanager.h ]
// Author : Asuma Nishio
//
//=================================================

#ifndef _RUBBLEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _RUBBLEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubble.h"
#include <vector>

//**********************************
// ���I�Ǘ��N���X���`
//**********************************
class CRubbleManager
{
public:
	//*************************
	// �g���t�@�C���p�X�̎��
	//*************************
	enum FILETYPE
	{
		FILETYPE_SMALL,
		FILETYPE_MEDIUM,
		FLIETYPE_lARGE,
		FILETYPE_MAX
	};

	CRubbleManager();
	~CRubbleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(void);

	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:
	static std::vector<CRubble*> m_rubbles; // ���I�z��
	static int m_nIdxCount;	// ���f���C���f�b�N�X�ԍ�

	static constexpr const char* FILEPASS = "data\\Loader\\RubbleList.txt"; // �t�@�C���p�X

};

#endif

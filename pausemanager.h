//====================================
//
// �|�[�Y�Ǘ����� [ pausemanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PAUSEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _PAUSEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "pause.h"

//*********************************
// �|�[�Y���j���[�Ǘ��N���X���`
//*********************************
class CPauseManager
{
public:
	CPauseManager();
	~CPauseManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetEnablePause(bool isFlags) { m_isPause = isFlags; }
	void SetEnablePause(void);

	static bool GetPause(void) { return m_isPause; }

private:
	static constexpr int SELECT_MAX = 4; // �ő僁�j���[�I��
	static constexpr float SPACEHEIGHT = 160.0f; // �|���S�����m�̊Ԋu

	int m_nSelectIdx;	// �Z���N�g�ԍ�
	static bool m_isPause;		// �|�[�Y���ǂ���
	CPause* m_pPause[SELECT_MAX]; // �|�[�Y�N���X�̃|�C���^�z��
	
};

#endif

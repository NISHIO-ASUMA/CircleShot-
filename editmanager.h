//============================================
//
// �G�f�B�^�[�V�[���Ǘ����� [ editmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _EDITMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _EDITMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

class CRubble;
class CMapManager;

#include "modellist.h"

//**********************************
// �G�f�B�^�[�Ǘ��N���X���`
//**********************************
class CEditManager
{
public:
	CEditManager();
	~CEditManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);

private:

	static constexpr int MAX_EDITOBJ = 256;

	int m_nSelectIndex; // �I�𒆃I�u�W�F�N�g�̃C���f�b�N�X
	float m_moveSpeed;
	float m_rotSpeed;

	CRubble* m_pRubbleObj[MAX_EDITOBJ]; 	// Rubble�̃I�u�W�F�N�g�|�C���^
	CMapManager* m_pMapManager;
};

#endif

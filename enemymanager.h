//====================================
//
// �G�̊Ǘ����s�� [ enemymanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ENEMYMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _ENEMYMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "enemy.h"

//******************************
// �G�Ǘ��N���X���`
//******************************
class CEnemymanager
{
public:
	CEnemymanager();
	~CEnemymanager();

	void Create(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nManagEnemy; // �����G���ۑ�
};
#endif
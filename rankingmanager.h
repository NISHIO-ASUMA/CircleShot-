//==========================================
//
// �����L���O�Ǘ����� [ rankingmanager.h ]
// Author: Asuma Nishio
//
//==========================================

#ifndef _RANKINGMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _RANKINGMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
class CRankingManager
{
public:
	CRankingManager();
	~CRankingManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

#endif
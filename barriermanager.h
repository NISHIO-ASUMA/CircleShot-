//===================================================
//
// �o���A�I�u�W�F�N�g�̊Ǘ����� [ barriermanager.h ]
// Author : Asuma Nishio
//
//===================================================

#ifndef _BARRIERMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _BARRIERMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//************************************
// �o���A�I�u�W�F�N�g�Ǘ��N���X���`
//************************************
class CBarrierManager
{
public:
	CBarrierManager();
	~CBarrierManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

#endif
//===================================================
//
// �o���A�I�u�W�F�N�g�̊Ǘ����� [ barriermanager.h ]
// Author : Asuma Nishio
//
//===================================================

#ifndef _BARRIERMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _BARRIERMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//************************************
// �O���錾
//************************************
class CBarrierDurability;

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

	int GetNumBarrier() const { return m_nBarrierNum; }

	void AddBarrier(int nValue);		// �o���A���Z
	void DamageBarrier(int nValue);		// �G�U����

private:
	int m_nBarrierNum; // �o���A����
	CBarrierDurability* m_pBarrierUI; // UI�`��p�|�C���^

};

#endif
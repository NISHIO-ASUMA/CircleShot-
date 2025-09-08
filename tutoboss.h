//==========================================
//
// �`���[�g���A���{�X���� [ tutoboss.h ]
// Author: Asuma Nishio
//
//==========================================

#ifndef _TUTOBOSS_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTOBOSS_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// �`���[�g���A���{�X�N���X���`
//********************************
class CTutoBoss : public CObject
{
	//***************************
	// ���[�V�����񋓌^�錾
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL,	// �j���[�g����
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTutoBoss(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutoBoss();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTutoBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	static constexpr int TUTOMODEL = 21; // �g�����f����

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;	// �}�g���b�N�X

	CModel* m_pModel[TUTOMODEL]; // ���f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����|�C���^
	int m_nType;

};

#endif
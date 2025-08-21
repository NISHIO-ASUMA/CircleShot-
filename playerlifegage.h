//=========================================
//
// �v���C���[�̗͏��� [ playerlifegage.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _PLAYERLIFEGAGE_H_ // ���̃}�N����`������ĂȂ�������
#define _PLAYERLIFEGAGE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "gage.h"

//**********************
// �O���錾
//**********************
class CPlayer;

//*************************
// �̗̓Q�[�W�N���X���`
//*************************
class CPlayerLifeGage : public CGage
{
public:
	//**********************
	// �Q�[�W�̎�ޒ�`
	//**********************
	enum GAGE
	{
		GAGE_FRAME,
		GAGE_BAR,
		GAGE_MAX
	};

	CPlayerLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPlayerLifeGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype);

	void SetTexture(int Type);
	int GetGage(void) const { return m_gage; }
	void SetGage(int type) { m_gage = type; }

private:
	static constexpr float GAGE_WIDTH = 40.0f;	// ��l�Ɋ|����{��
	static constexpr float GAGE_HEIGHT = 45.0f; // �Q�[�W�̍����̌Œ�l

	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
	int m_nLifeLength;		// �o�[�̒�����l
	int m_nMaxLifeLength;	// �ŏ��̗̑͒l
	CPlayer* m_pPlayer;		// �v���C���[�N���X�|�C���^
	int m_gage;			// �񋓕ϐ�


};

#endif

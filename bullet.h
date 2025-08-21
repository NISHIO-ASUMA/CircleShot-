//====================================
//
// �e�̏��� [ bullet.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BULLET_H_ // ���̃}�N����`������ĂȂ�������
#define _BULLET_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"
#include "object.h"

//**************************
// �e�N���X���`
//**************************
class CBullet : public CBillboard
{
public:

	// �e�̎�ނ��`
	enum BTYPE
	{
		BTYPE_NONE = 0,
		BTYPE_PLAYER,
		BTYPE_ENEMY,
		BTYPE_HOWMING,
		BTYPE_MAX
	};

	CBullet(int nPriority = static_cast<int>(CObject::PRIORITY::BULLET));
	~CBullet();

	HRESULT Init(D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet* Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 rot,BTYPE nType,const float fWidth, const float fHeight, const int nLife);

	void SetType(BTYPE type);
	BTYPE GetType(void) { return m_Type; }
	void SetTexture(BTYPE type);

	bool Collision(D3DXVECTOR3 pos); // �����蔻��p�֐�

private:

	D3DXVECTOR3 m_move;		// �ړ���
	BTYPE m_Type;			// ���
	D3DCOLOR m_col;			// �e�̃J���[
	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
	int m_nLife;			// �̗�

};
#endif

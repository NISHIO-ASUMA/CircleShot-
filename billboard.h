//====================================
//
// �r���{�[�h���� [ billboard.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BILLBOARD_H_ // ���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//*************************
// �r���{�[�h�N���X���`
//*************************
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXCOLOR GetCol(void) { return m_col; };

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetTexture(void);
	void SetEnableZtest(bool isflags) { m_isTests = isflags; }

	void Flash(const int nMaxFlashTime,const int Digittime);

	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // ���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_rot;  // �p�x���
	D3DXVECTOR3 m_pos;  // ���W���
	D3DXCOLOR m_col;    // �F���

	int m_nIdxTexture;			// �e�N�X�`���C���f�b�N�X
	int m_FlashCount;
	float m_fHeight, m_fWidth;  // ����,����
	bool m_isTests;			// Z�e�X�g���邩�ǂ���
};

#endif
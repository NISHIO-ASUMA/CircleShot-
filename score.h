//====================================
//
// �X�R�A���� [ score.h ]
// Author: Asuma Nishio
//
// TODO : 2D�͎�O�ɕ`�悷��̂Ŕԍ���7
// 
//=====================================

#ifndef _SCORE_H_ // ���̃}�N����`������ĂȂ�������
#define _SCORE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "number.h"
#include "object.h"

//*******************************************
// �X�R�A�N���X���` ( �I�u�W�F�N�g�p�� )
//*******************************************
class CScore : public CObject
{
public:
	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void AddScore(int nValue);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetTexture(void);

	static inline constexpr int NUM_SCORE = 8; // ����

private: 
	
	static int m_nScore;			// �X�R�A�ێ��p

	CNumber *m_apNumber[NUM_SCORE];	// �������̃i���o�[�̃|�C���^
	D3DXCOLOR m_col;				// �J���[
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_rot;				// �p�x]
	

	float m_fWidth;					// ����
	float m_fHeight;				// ����
	int m_nIdxTexture;				// �e�N�X�`���C���f�b�N�X


};
#endif
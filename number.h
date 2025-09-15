//====================================
//
// �������� [ number.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _NUMBER_H_ // ���̃}�N����`������ĂȂ�������
#define _NUMBER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �i���o�[�N���X���`
//**********************
class CNumber
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CNumber();
	~CNumber();

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, float fwidth, float fheight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos;}
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetDigit(int nDigit);

private:
	static constexpr float DIGIT_VALUE = 0.1f; // �e�N�X�`������������

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^

	D3DXVECTOR3 m_pos;				// ���W���
	float m_fWidth, m_fHeight;		// ����,����
	float m_TexU, m_TexU1,m_TexV;	// �e�N�X�`�����W
};

#endif
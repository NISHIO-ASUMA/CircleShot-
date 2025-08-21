//====================================
//
// �X�R�A���� [ score.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "score.h"
#include "manager.h"

//**************************
// �萔�錾
//**************************
constexpr int NUM_DIGIT = 10; // �\�����镪�������̒l

//**********************
// �ÓI�����o�ϐ��錾
//**********************
int CScore::m_nScore = 0;	// ���X�R�A�J�E���g�p

//==========================================
// �R���X�g���N�^
//==========================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_nScore = NULL;
	m_nIdxTexture = NULL;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}
//==========================================
// �f�X�g���N�^
//==========================================
CScore::~CScore()
{
	// ����
}
//==========================================
// ��������
//==========================================
CScore* CScore::Create(D3DXVECTOR3 pos,float fWidth,float fHeight)
{
	// �X�R�A�C���X�^���X����
	CScore* pScore = new CScore;

	// nullptr��������
	if (pScore == nullptr) return nullptr;

	// ���W,�T�C�Y�ݒ�
	pScore->m_pos = pos;
	pScore->m_fWidth = fWidth;
	pScore->m_fHeight = fHeight;

	// ���������s��
	if (FAILED(pScore->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}
	
	// �X�R�A�|�C���^��Ԃ�
	return pScore;
}
//==========================================
// ����������
//==========================================
HRESULT CScore::Init(void)
{
	// �����v�Z
	float fTexPos = m_fWidth / NUM_SCORE;

	// ������
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// �C���X�^���X����
		m_apNumber[nCnt] = new CNumber;

		// �i���o�[�ϐ��̃T�C�Y
		m_apNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// ���W�ݒ�
		m_apNumber[nCnt]->SetPos(m_pos);

		// ����������
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y,0.0f), fTexPos, m_fHeight);
	}

	// �e�N�X�`���Z�b�g
	SetTexture();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==========================================
// �I������
//==========================================
void CScore::Uninit(void)
{
	// �g�������j��
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_apNumber[nCnt] != nullptr)
		{
			// �I��
			m_apNumber[nCnt]->Uninit();

			// �j��
			delete m_apNumber[nCnt];

			// �|�C���^������
			m_apNumber[nCnt] = nullptr;
		}
	}

	// ���g�̔j��
	CObject::Release();
}
//==========================================
// �X�V����
//==========================================
void CScore::Update(void)
{
	// �X�R�A�i�[
	int score = m_nScore;

	// ������
	for (int nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++) // �E���珈��
	{
		// �����v�Z�p�ϐ�
		int digit = score % NUM_DIGIT;
		score /= NUM_DIGIT;

		// �i���o�[�X�V
		m_apNumber[nCntScore]->Update();

		// ���X�V
		m_apNumber[nCntScore]->SetDigit(digit);
	}
}
//==========================================
// �`�揈��
//==========================================
void CScore::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �g���Ă��錅�����̕`��
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// �e�N�X�`���Z�b�g
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		// �i���o�[�`��
		m_apNumber[nCnt]->Draw();
	}
}
//==========================================
// �X�R�A�ݒ菈��
//==========================================
void CScore::AddScore(int nValue)
{
	// �X�R�A���Z
	m_nScore += nValue;
}
//==========================================
// �e�N�X�`���ݒ�
//==========================================
void CScore::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\num001.png");
}

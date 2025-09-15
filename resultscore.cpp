//=======================================
//
// ���U���g�X�R�A���� [ resultscore.h ]
// Author: Asuma Nishio
// 
//=======================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "resultscore.h"
#include "manager.h"
#include "texture.h"

//================================
// �R���X�g���N�^
//================================
CResultScore::CResultScore(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_nScore = NULL;
	m_nLastScore = NULL;
	m_nTimeScore = NULL;
	m_nIdxTexture = NULL;

	m_pos = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}
//================================
// �f�X�g���N�^
//================================
CResultScore::~CResultScore()
{
	// ����
}
//================================
// ��������
//================================
CResultScore* CResultScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	// �C���X�^���X����
	CResultScore* pResultScore = new CResultScore;
	if (pResultScore == nullptr) return nullptr;

	// ���W,�T�C�Y�ݒ�
	pResultScore->m_pos = pos;
	pResultScore->m_fWidth = fWidth;
	pResultScore->m_fHeight = fHeight;
	pResultScore->m_nType = nType;

	// ���������s��
	if (FAILED(pResultScore->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pResultScore;
}
//================================
// ����������
//================================
HRESULT CResultScore::Init(void)
{
	// �����v�Z
	float fTexPos = m_fWidth / NUM_RESULTSCORE;

	// ������
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// �C���X�^���X����
		m_apNumber[nCnt] = new CNumber;

		// �i���o�[�ϐ��̃T�C�Y
		m_apNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// ���W�ݒ�
		m_apNumber[nCnt]->SetPos(m_pos);

		// ����������
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);
	}

	// �e�N�X�`���Z�b�g
	SetTexture();

	// ���������ʂ�Ԃ�
	return S_OK;

}
//================================
// �I������
//================================
void CResultScore::Uninit(void)
{
	// �g�������j��
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
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
//================================
// �X�V����
//================================
void CResultScore::Update(void)
{
	switch (m_nType)
	{
	case SCORE_GAME:
	{
		// �X�R�A�i�[
		int nScore = m_nScore;

		// ������
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // �E���珈��
		{
			// �������Ƃɕ�������l���v�Z
			int nDigit = nScore % NUM_RESULTDIGIT;

			nScore /= NUM_RESULTDIGIT;

			// �i���o�[�X�V
			m_apNumber[nCntScore]->Update();

			// ���X�V
			m_apNumber[nCntScore]->SetDigit(nDigit);
		}
	}
	break;

	case SCORE_TIME:
	{
		// �^�C���p�̃X�R�A�i�[
		int nTimescore = m_nTimeScore;

		// ������
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // �E���珈��
		{
			// �������Ƃɕ�������l���v�Z
			int nDigitTime = nTimescore % NUM_RESULTDIGIT;

			nTimescore /= NUM_RESULTDIGIT;

			// �i���o�[�X�V
			m_apNumber[nCntScore]->Update();

			// ���X�V
			m_apNumber[nCntScore]->SetDigit(nDigitTime);
		}
	}
	break;

	case SCORE_LAST:
	{
		// �X�R�A�i�[
		int nLastScore = m_nLastScore;

		// ������
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // �E���珈��
		{
			// �������Ƃɕ�������l���v�Z
			int nDigitLast = nLastScore % NUM_RESULTDIGIT;

			nLastScore /= NUM_RESULTDIGIT;

			// �i���o�[�X�V
			m_apNumber[nCntScore]->Update();

			// ���X�V
			m_apNumber[nCntScore]->SetDigit(nDigitLast);
		}
	}
	break;

	default:
		break;
	}
}
//================================
// �`�揈��
//================================
void CResultScore::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �g���Ă��錅�����̕`��
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// �e�N�X�`���Z�b�g
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		// �i���o�[�`��
		m_apNumber[nCnt]->Draw();
	}
}
//================================
// �e�N�X�`������
//================================
void CResultScore::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\num001.png");
}
//================================
// �N���A�^�C���̃X�R�A���v�Z
//================================
int CResultScore::MathTimescore(void)
{
	// �ǂݍ��񂾒l
	float fValue = (float)m_nTimeScore;

	// ����l
	const float fMaxReadValue = 120.0f;

	// �ő�X�R�A
	const int nMaxTimeScore = 50000;

	// �䗦���Z�o
	float fRatio = 1.0f - (fValue / fMaxReadValue);

	// �͈͕␳
	if (fRatio < 0.0f) fRatio = 0.0f;
	if (fRatio > 1.0f) fRatio = 1.0f;

	// �X�R�A�v�Z
	int nMathscore = (int)(nMaxTimeScore * fRatio);

	return nMathscore;
}

//========================================
//
// ���I�I�u�W�F�N�g���� [ rubble.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubble.h"
#include "scene.h"
#include "manager.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CRubble::CRubble(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_Fallingspeed = VECTOR3_NULL;
}
//================================
// �f�X�g���N�^
//================================
CRubble::~CRubble()
{
	// ����
}
//================================
// ����������
//================================
HRESULT CRubble::Init(void)
{
	// �e�N���X����������
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ޒ�`
	SetObjType(CObject::TYPE_BLOCK);

	// �����l��ݒ�
	m_Fallingspeed = { 0.0f,1.5f,0.0f };

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CRubble::Uninit(void)
{
	// �e�N���X�I������
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CRubble::Update(void)
{
	// ���݃V�[���擾
	CScene::MODE pMode = CManager::GetScene();

	if (pMode == CScene::MODE_GAME)
	{
		// ���݂̍��W���擾
		D3DXVECTOR3 NowPos = GetPos();

		// ���݂̍��W�ɑ΂��ďd�͒l�����Z����
		NowPos -= m_Fallingspeed;

		// ���ݍ��W���Z�b�g����
		SetPos(NowPos);
	}
}
//================================
// �`�揈��
//================================
void CRubble::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
//================================
// ��������
//================================
CRubble* CRubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// �C���X�^���X����
	CRubble* pRubble = new CRubble;

	// ����null��������
	if (pRubble == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pRubble->SetFilePass(pFilename);
	pRubble->SetPos(pos);
	pRubble->SetRot(rot);

	// ���������s��
	if (FAILED(pRubble->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pRubble;
}

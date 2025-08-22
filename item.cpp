//===================================
//
// �A�C�e������ [ item.cpp ]
// Author: Asuma Nishio
//
//===================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "item.h"
#include "template.h"

//**************************
// ���O���
//**************************
namespace ITEMINFO
{
	inline  constexpr float HITRANGE = 50.0f; // �����蔼�a�͈̔�
};

//=================================
// �I�[�o�[���[�h�R���X�g���N�^
//=================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CItem::~CItem()
{
	// ����
}
//=================================
// ��������
//=================================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* Filename)
{
	// �C���X�^���X����
	CItem* pItem = new CItem;

	// null�Ȃ�
	if (pItem == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pItem->SetFilePass(Filename);
	pItem->SetPos(pos);
	pItem->SetRot(rot);

	// ���������s��
	if (FAILED(pItem->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^
	return pItem;
}
//=================================
// ����������
//=================================
HRESULT CItem::Init(void)
{
	// �e�N���X�̏���������
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ޒ�`
	SetObjType(TYPE_ITEM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CItem::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//=================================
// �X�V����
//=================================
void CItem::Update(void)
{
	// ���݂̊p�x���擾
	D3DXVECTOR3 rot = GetRot();

	// ��]�p�����Z
	rot.y += 0.03f;

	// �p�x���K���֐�
	rot.y = NormalAngle(rot.y);

	// �p�x�Z�b�g
	SetRot(rot);
}
//=================================
// �`�揈��
//=================================
void CItem::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}
//=================================
// �����蔻�菈��
//=================================
bool CItem::Collision(D3DXVECTOR3* pPos)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// ���݂̍��W���甼�a���v�Z
	D3DXVECTOR3 CollisionPos = NowPos - *pPos;

	// �͈͓��Ȃ�
	if (D3DXVec3Length(&CollisionPos) <= ITEMINFO::HITRANGE)
	{
		// �Ώۂ̃I�u�W�F�N�g����
		Uninit();

		// �q�b�g�����Ԃ�
		return true;
	}

	// �������ĂȂ��Ƃ�
	return false;
}

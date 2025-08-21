//====================================
//
// �e�̏��� [ bullet.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "bullet.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"
#include "boss.h"
#include "particle.h"
#include "gamemanager.h"

//*******************************
// �萔�錾
//*******************************
namespace BulletConst
{
	constexpr float  BULLET_SIZE = 30.0f;	// �e�̃T�C�Y
	constexpr int  BULLET_DAMAGE = 1;		// �e�̃_���[�W
}

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CBullet::CBullet(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_nLife = NULL;
	m_move = VECTOR3_NULL;
	m_Type = BTYPE_NONE;
	m_nIdxTexture = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CBullet::~CBullet()
{
	// ����
}
//===============================
// �e�̐���
//===============================
CBullet* CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, BTYPE nType, const float fWidth, const float fHeight,const int nLife)
{
	// �ő吔
	int nNum = CObject::GetNumAll();

	// �ő吔��������
	if (nNum >= MAX_OBJECT -1)
	{
		// null��Ԃ�
		return nullptr;
	}

	// �e�̃C���X�^���X����
	CBullet* pBullet = new CBullet;

	// �C���X�^���X�̐����Ɏ��s������
	if (pBullet == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBullet->SetTexture(nType);
	pBullet->SetPos(pos);
	pBullet->SetType(nType);
	pBullet->SetSize(fWidth, fHeight);
	pBullet->m_nLife = nLife;

	// �������Ɏ��s������
	if (FAILED(pBullet->Init(rot)))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pBullet;
}
//===============================
// �e�̎�ރZ�b�g
//===============================
void CBullet::SetType(BTYPE type)
{
	// ��ސݒ�
	m_Type = type;
}
//===============================
// ��ނ��Ƃ̃e�N�X�`���Z�b�g
//===============================
void CBullet::SetTexture(BTYPE type)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ݒ�
	switch (type)
	{
	case BTYPE_PLAYER:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\bullet002.png");
		break;

	case BTYPE_ENEMY:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gold.jpg");
		break;

	default:
		break;
	}
}
//===============================
// �e�̏�����
//===============================
HRESULT CBullet::Init(D3DXVECTOR3 rot)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�̎�ނ�ݒ肷��
	SetObjType(TYPE_BULLET);

	// �ړ��ʂ��v�Z
	m_move = D3DXVECTOR3(rot.x * 15.0f, rot.y,rot.z * 15.0f);

	return S_OK;
}
//===============================
// �e�̏I��
//===============================
void CBullet::Uninit(void)
{
	// �e�N���X�̔j��
	CBillboard::Uninit();
}
//===============================
// �e�̍X�V
//===============================
void CBullet::Update(void)
{
	// �e�̍��W���擾
	D3DXVECTOR3 BulletPos = GetPos();

	// ���������X�Ɍ��炷
	m_nLife--;

	// �J���[�Z�b�g
	SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	// �G�t�F�N�g����
	CEffect::Create(BulletPos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), VECTOR3_NULL, m_nLife, 10.0f);

	// �ʒu���X�V
	BulletPos += m_move;

	// ���W���X�V
	SetPos(BulletPos);

	// �G�Ƃ̓����蔻��
	bool isHit = Collision(BulletPos);

	// �̗͂�0�ȉ� ���� �G�ɓ������Ă��Ȃ�������
	if (m_nLife <= 0 && !isHit)
	{
		// ���g�p���
		Uninit();
	}
}
//===============================
// �e�̕`��
//===============================
void CBullet::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �I�u�W�F�N�g�̕`��
	CBillboard::Draw();
}
//====================================
// �����蔻�菈�� ( ���� : �e�̍��W )
//====================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	// �{�X�擾
	CBoss* pBoss = CGameManager::GetBoss();

	// �I�u�W�F�N�g���擾�ł�����
	if (pBoss != nullptr)
	{
		// �e�̎�ނ��擾
		BTYPE Type = GetType();

		if (Type == BTYPE_PLAYER)
		{
			// �{�X�̍��W,�T�C�Y�擾
			D3DXVECTOR3 BossPos = pBoss->GetPos();
			float fBossSize = pBoss->GetSize();

			// �e�̍��W��Y���{�X��Y�ɍ��킹��
			pos.y = BossPos.y;

			// XZ���ʏ�̋������v�Z
			D3DXVECTOR3 diff = BossPos - pos;

			float fDistanceSq = D3DXVec3LengthSq(&diff);

			// �{�X�ƒe�̔��a�̍��v
			float fBulletRadius = BulletConst::BULLET_SIZE;

			// �q�b�g�̔��a���v�Z
			float fHitRadius = fBossSize + fBulletRadius;

			// ����͈̔͂��v�Z
			float fLength = fHitRadius * fHitRadius;

			// �͈͓��Ȃ�
			if (fDistanceSq <= fLength)
			{
				// �e�X�g�Ńp�[�e�B�N������
				CParticle::Create(D3DXVECTOR3 (BossPos.x,30.0f,BossPos.z), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), 35, 150, 100, 300);

				// �{�X�Ƀ_���[�W
				pBoss->Hit(3);

				// �e������
				CBullet::Uninit();

				// �������������Ԃ�
				return true;
			}
		}
	}

	// ������Ȃ��Ƃ�
	return false;
}

//=============================================
//
// �����蔻��̊Ǘ����s�� [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include "collision.h"

//*******************************
// �R���X�g���N�^
//*******************************
CCollision::CCollision()
{
    // �Ȃ�
}
//*******************************
// �f�X�g���N�^
//*******************************
CCollision::~CCollision()
{
    // ����
}
//*******************************
// ���`�����蔻��
//*******************************
D3DXVECTOR3 CCollision::CollisionSphere(D3DXVECTOR3* outPos, D3DXVECTOR3* pPos, D3DXVECTOR3* pPos1,float CollsionSize)
{
    // �܂�,2�_�Ԃ̃x�N�g�������߂�
    D3DXVECTOR3 Vec = VECTOR3_NULL;

    Vec.x = pPos1->x - pPos->x;
    Vec.y = pPos1->y - pPos->y;
    Vec.z = pPos1->z - pPos->z;

    // �v�Z�����x�N�g���̒������擾����
    float fLength = D3DXVec3Length(&Vec);

    // �v�Z�����͈͓��ɓ����Ă�����
    if (fLength < CollsionSize)
    {
        // �x�N�g���̐��K��������
        D3DXVec3Normalize(&Vec,&Vec);
        
        // �߂荞�ݗʂ��������v�Z����
        float fDestLength = CollsionSize - fLength; // �߂荞�ݗ�

        // �o�͂�����W���v�Z����
        outPos->x = pPos1->x + Vec.x * fDestLength;
        outPos->y = pPos1->y + Vec.y * fDestLength;
        outPos->z = pPos1->z + Vec.z * fDestLength;
    }
    else
    {
        // ������Ȃ��Ƃ��͌��̈ʒu��Ԃ�
       *outPos = *pPos;
    }

    // �����߂������W��Ԃ�
    return *outPos;
}

//=============================================
//
// �����蔻��̊Ǘ����s�� [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _COLLISION_H_ // ���̃}�N����`������ĂȂ�������
#define _COLLISION_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//************************************
// �R���W�����N���X���`
//************************************
class CCollision
{
public:
	CCollision();
	~CCollision();

	D3DXVECTOR3 CollisionSphere(D3DXVECTOR3* outPos, D3DXVECTOR3* pPos, D3DXVECTOR3* pPos1, float CollsionSize);

private:

};

#endif // !_COLLISION_H_







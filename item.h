//===================================
//
// �A�C�e������ [ item.h ]
// Author: Asuma Nishio
//
//===================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "objectX.h"

//****************************
// �O���錾
//****************************
class CObject;

//****************************
// �A�C�e���N���X���`
//****************************
class CItem : public CObjectX
{
public:
	CItem(int nPriority = static_cast<int>(CObject::PRIORITY::ITEM));
	~CItem();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char* Filename);

	bool Collision(D3DXVECTOR3* pPos);

private:
};


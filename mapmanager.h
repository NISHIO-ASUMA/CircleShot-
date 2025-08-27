//========================================
//
// �}�b�v�}�l�[�W���[���� [ mapmanager.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _MAPMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _MAPMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C��
//***************************
#include "object.h"
#include <vector>

//***************************
// �O���錾
//***************************
class CMapObject;

//***************************
// �}�b�v�}�l�[�W���[�N���X
//***************************
class CMapManager : CObject
{
public:
	CMapManager(int nPriority = static_cast<int>(CObject::PRIORITY::BLOCK));
	~CMapManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CMapObject* GetInfo(const int nIdx) { return m_MapObj[nIdx]; }

	void PushBack(CMapObject* pMapOjbect) { m_MapObj.push_back(pMapOjbect); };
	static CMapManager* Craete(void);

private:
	std::vector<CMapObject*>m_MapObj;
	int m_nSelectIdx;

};

#endif

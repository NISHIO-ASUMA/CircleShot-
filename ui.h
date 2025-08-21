//====================================
//
// UI���� [ ui.h ]
// Author: Asuma Nishio
//
//=====================================
#ifndef _UI_H_ // ���̃}�N����`������ĂȂ�������
#define _UI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "object2D.h"

//****************************
// UI�N���X���`
//****************************
class CUi : public CObject2D
{
public:

	//***************************
	// UI�̎�ޒ�`
	//***************************
	enum UITYPE
	{
		UITYPE_NONE,
		UITYPE_MOVE,
		UITYPE_MAX
	};

	CUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * Filename,int nAnchorType);

	void SetTexture(const char * pRegistername);

private:
	int m_nTexIdxType;		// �e�N�X�`���C���f�b�N�X
	int m_type;
};

#endif
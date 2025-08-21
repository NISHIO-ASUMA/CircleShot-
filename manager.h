//====================================
//
// �}�l�[�W���[���� [ manager.h ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// ��d�C���N���[�h�K�[�h
//**************************
#ifndef _MANAGER_H_ 
#define _MANAGER_H_ 

//**************************  
// �C���N���[�h�t�@�C���錾
//**************************
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "bullet.h"
#include "enemymanager.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "blockManager.h"
#include "collision.h"
#include "meshcylinder.h"
#include "boss.h"
#include "scene.h"
#include "fade.h"

//**************************
// �}�l�[�W���[�N���X�錾
//**************************
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetInputKeyboard(void);
	static CJoyPad* GetJoyPad(void);
	static CSound* GetSound(void);
	static CInputMouse* GetMouse(void);
	static CTexture* GetTexture(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);

	static void SetScene(CScene * pNewScene); // ��������V�[���̃C���X�^���X������
	static CScene::MODE GetScene(void);

	static CFade* GetFade(void);

private:
	static CRenderer* m_pRenderer;			 // �����_���[�N���X�̃|�C���^
	static CInputKeyboard* m_pInputKeyboard; // �L�[�{�[�h�N���X�̃|�C���^
	static CJoyPad* m_pJoyPad;				 // �W���C�p�b�h�N���X�̃|�C���^
	static CSound* m_pSound;				 // �T�E���h�I�u�W�F�N�g�̃|�C���^
	static CInputMouse* m_pInputMouse;		 // �}�E�X�N���X�̃|�C���^
	static CTexture* m_pTexture;			 // �e�N�X�`���N���X
	static CCamera* m_pCamera;				 // �J�����N���X
	static CLight* m_pLight;				 // ���C�g�N���X

	static CScene* m_pScene;		// �V�[���Ǘ�
	static CFade* m_pFade;			// �t�F�[�h
};
#endif
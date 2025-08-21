//=====================================
//
// �e�N�X�`������ [ texture.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TEXTURE_H_ // ���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*****************************
// �e�N�X�`���Ǘ��N���X���`
//*****************************
class CTexture
{
public:
	//*****************************
	// �e�N�X�`���̎��
	//*****************************
	enum TYPE
	{
		TYPE_LOGO,
		TYPE_TITLEMENU1,
		TYPE_TITLEMENU2,
		TYPE_MAX,
	};

	CTexture();
	~CTexture();

	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

	void TextLoader(const char* pFileName);

	static inline constexpr int NUM_TEXTURE = 128;	// �ő�e�N�X�`����

private:
	// �e�N�X�`���ǂݍ��ݔz����쐬
	const char* TexName[NUM_TEXTURE] =
	{
		"data\\TEXTURE\\explosion000.png",
		"data\\TEXTURE\\effect000.jpg",
		"data\\TEXTURE\\bullet002.png",
		"data\\TEXTURE\\num001.png",
		"data\\TEXTURE\\field000.jpeg",
		"data\\TEXTURE\\DomeTex.jpg",
		"data\\TEXTURE\\shadow000.jpg",
		"data\\TEXTURE\\lifegage.png",
		"data\\TEXTURE\\lifeframe.png",
		"data\\TEXTURE\\score001.png",
		"data\\TEXTURE\\PauseBack.png",
		"data\\TEXTURE\\titlemenu001.png",
		"data\\TEXTURE\\titilemenu_002.png",
		"data\\TEXTURE\\tutorial_menu.png",
		"data\\TEXTURE\\logo.png",
		"data\\TEXTURE\\Enterkey.png",
		"data\\TEXTURE\\boss_life.png",
		"data\\TEXTURE\\boss_frame.png",
		"data\\TEXTURE\\pausemenu_continue.png",
		"data\\TEXTURE\\pausemenu_retry.png",
		"data\\TEXTURE\\pausemenu_quit.png",
		"data\\TEXTURE\\resultlogo.png",
		"data\\TEXTURE\\playerlife_frame000.png",
		"data\\TEXTURE\\playerlife_gage000.png",
		"data\\TEXTURE\\time000.png",
		"data\\TEXTURE\\alert.png",
		"data\\TEXTURE\\alert_frame.png",
	};

	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXTURE];	// �e�N�X�`���|�C���^
	static int m_nNumAll;							// �e�N�X�`���J�E���g�ϐ�
};

#endif
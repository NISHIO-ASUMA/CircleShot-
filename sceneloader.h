//====================================================
//
// �V�[���t�@�C���ǂݍ��ݏ��� [ sceneloader.h ]
// Author: Asuma Nishio
//
//====================================================

//**********************************
// �X�N���v�g�t�@�C���ǂݍ��ݏ���
//**********************************
class CSceneLoader
{
public:
	CSceneLoader();
	~CSceneLoader();

	static void SplitLoad(int nIdx);

private:
	static constexpr int NUMFILE = 2;

	// �t�@�C�����X�g
	static constexpr const char* m_aFileList[] = {
		"data\\SceneText\\TutoObj.txt",	// [0] �`���[�g���A��
		"data\\SceneText\\GameObj.txt",	// [1] �Q�[��
	};

};


//=====================================
//
// �J�������� [ camera.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _CAMERA_H_ // ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �O���錾
//**********************
class CInputMouse;

//**********************
// �J�����N���X���`
//**********************
class CCamera
{
public:
	//**********************
	// �J�������[�h�񋓌^
	//**********************
	enum MODE
	{
		MODE_NONE = 0,
		MODE_PLAYER,
		MODE_LOCKON,
		MODE_MOUSE,
		MODE_EVENT,
		MOMDE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CCamera();
	~CCamera();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void MouseView(CInputMouse* pMouse);
	void LockOn(void);
	void PlayerFollow(void);
	void Rotation(void);
	void TitleCamera(void);

	// �Z�b�^�[
	void StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame);
	void ShakeCamera(int WaveTime);
	void SetIsRotation(bool isFlags) { m_isRotation = isFlags; }
	void SetFinishRotation(bool isFlags) { m_isStopRotation = isFlags; }
	void SetCameraMode(int nMode) { m_pCamera.nMode = nMode; }

	// �Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }


	// �t���O�����g
	bool GetIsRotation(void) { return m_isRotation; }
	bool GetFinishRotation(void) { return m_isStopRotation; }

private:
	//*************************
	// �J�����\���̂��`
	//*************************
	struct Camera
	{
		D3DXMATRIX mtxprojection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
		D3DXVECTOR3 posV, posR;		// ���_,�����_���W
		D3DXVECTOR3 rot;			// �p�x
		D3DXVECTOR3 vecU;			// �@���x�N�g��
		D3DXVECTOR3 posRDest;		// �ړI���W
		float fDistance;			// �J�����̋���
		int nMode;				// �J�����̃��[�h
	};

	Camera m_pCamera;	// �\���̕ϐ�
	bool m_isRotation;	// ��]�������ǂ���
	bool m_isStopRotation;	// ��]�I��

	D3DXVECTOR3 m_lastBossPos;		// �{�X�̍Ō�̍��W
	bool m_isSetPos;		// �{�X�����񂾂��ǂ����̃t���O

	int m_nShakeTime;
	bool m_isShake;

	//*************************
	// �C�x���g�t���[���\����
	//*************************
	struct EventData
	{
		bool isActive = false;	// �C�x���g���s����
		int	 frame = 0;			// �o�߃t���[��
		int	 endFrame = 0;		// �I���t���[��
		D3DXVECTOR3 startPosV;		// �J�n���_
		D3DXVECTOR3 startPosR;		// �J�n�����_
		D3DXVECTOR3 targetPosV;		// �ڕW���_
		D3DXVECTOR3 targetPosR;		// �ڕW�����_
	};

	EventData m_event;				// �C�x���g�p�f�[�^
};

#endif
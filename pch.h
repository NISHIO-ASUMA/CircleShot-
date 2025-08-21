//====================================
//
// �v���R���p�C���w�b�_�[ [ pch.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PCH_H_ // ���̃}�N����`������ĂȂ�������
#define _PCH_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include <windows.h>
#include "d3dx9.h"					// �`�揈���ɕK�v
#include "d3d9.h"
#define DIRECTINPUT_VERSION (0x0800)// �r���h���x���Ώ��p�̃}�N��
#include "dinput.h"					// ���͏����ɕK�v
#include "Xinput.h"					// �W���C�p�b�h�����ɕK�v
#include "xaudio2.h"
#include <time.h>
#include <Shlwapi.h>
#include <assert.h>					// �A�T�[�g�֐��w�b�_�[
#include <stdlib.h>
#include <cstdio>

//**************************
// ���C�u�����̃����N�錾
//**************************
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")	// �W���C�p�b�h�����ɕK�v
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"shlwapi.lib")

//**************************
// �萔�錾
//**************************
inline const D3DXVECTOR3 VECTOR3_NULL = { 0.0f, 0.0f, 0.0f }; // ���W������

inline const D3DXCOLOR COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };// ��
inline const D3DXCOLOR COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f }; // ��

inline const D3DXCOLOR COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f }; // ��
inline const D3DXCOLOR COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f }; // ��
inline const D3DXCOLOR COLOR_YERROW = { 1.0f, 1.0f, 0.0f, 1.0f }; // ���F
inline const D3DXCOLOR COLOR_BLUE = { 0.0f, 0.0f, 1.0f, 1.0f }; // ��

inline const D3DXCOLOR COLOR_NULL = { 0.0f, 0.0f, 0.0f, 0.0f } ; // ���S����
inline constexpr int MAX_WORD = 512;			// �ő啶���z��

//**************************
// �}�N����`
//**************************
#define SCREEN_WIDTH (1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// ���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_DIFFUSE | D3DFVF_TEX1)  // ���W,�@��,�J���[,�e�N�X�`��
#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2) // ���W,�@��,�J���[,�}���`�e�N�X�`��

//**********************
// ���_���[2D]�̍\����
//**********************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

//**********************
// ���_���[3D]�̍\����
//**********************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

//*****************************
// ���_���[3D_�}���`]�̍\����
//*****************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
	D3DXVECTOR2 texM;	// �}���`�e�N�X�`��
}VERTEX_3D_MULTI;

#endif
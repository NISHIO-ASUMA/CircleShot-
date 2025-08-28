//============================================
//
// �C�[�W���O���� [ easing.cpp ]
// Author: Asuma Nishio
//
//=============================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "easing.h"

//===============================
// �R���X�g���N�^
//===============================
CEasing::CEasing()
{

}
//===============================
// �f�X�g���N�^
//===============================
CEasing::~CEasing()
{

}

//===============================
// �Z�b�^�[
//===============================
float CEasing::SetEase(int EaseFrame, int MaxEaseFrame)
{
	// �t���[�����ő�܂ōs������~�߂�
	if (EaseFrame >= MaxEaseFrame)
	{
		EaseFrame = MaxEaseFrame;
	}

	// t�����߂�
	float t = (float)EaseFrame / (float)MaxEaseFrame;

	// t�̒l��Ԃ�
	return t;
}

//===============================
// �C�[�W���O�̊ɂ₩�ȉ���
//===============================
float CEasing::EaseInsine(float t)
{
	return 1 - cos((t * D3DX_PI) / 2);
}
//===============================
// �C�[�W���O�̊ɂ₩�Ȍ���
//===============================
float CEasing::EaseOutsine(float t)
{
	return sin((t * D3DX_PI) / 2);
}
//===================================
// �ɂ₩�ȉ���������
//===================================
float CEasing::EaseInOutSine(float t)
{
	return -(cos(D3DX_PI * t) - 1) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseInQuad(float t)
{
	return t * t;
}
//===================================
// 
//===================================
float CEasing::EaseOutQuad(float t)
{
	return 1 - (1 - t) * (1 - t);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuad(float t)
{
	return (float)t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseInCubic(float t)
{
	return t * t * t;
}
//===================================
// 
//===================================
float CEasing::EaseOutCubic(float t)
{
	return 1 - pow(1 - t, 3);
}
//===================================
// 
//===================================
float CEasing::EaseInOutCubic(float t)
{
	return (float)t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseBounce(float t)
{
	if (t < (1 / 2.75f))  // �ŏ��̃o�E���h
	{
		return 20.0f * t * t;  // �����𒲐����āA�o�E���h������
	}
	else if (t < (2 / 2.75f))  // 2�Ԗڂ̃o�E���h
	{
		t -= (1.5f / 2.75f);
		return 20.0f * t * t + 0.75f;  // �����𒲐����āA�o�E���h������
	}
	else if (t < (2.5f / 2.75f))  // 3�Ԗڂ̃o�E���h
	{
		t -= (2.25f / 2.75f);
		return 20.0f * t * t + 0.9375f;  // �����𒲐����āA�o�E���h������
	}
	else  // �Ō�̃o�E���h
	{
		t -= (2.625f / 2.75f);
		return 20.0f * t * t + 0.984375f;  // �����𒲐����āA�o�E���h������
	}
}

//===================================
// 
//===================================
float CEasing::EaseOutQuart(float t)
{
	return 1 - pow(1 - t, 4);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuart(float t)
{
	return t < 0.5 ? 8 * t * t * t * t : 1 - pow(-2 * t + 2, 4) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseOutQuint(float t)
{
	return 1 - pow(1 - t, 5);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuint(float t)
{
	return (float)t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2 * t + 2, 5) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseInBack(float t)
{
	const float s = 0.70158f;  // ��������x����
	return t * t * ((s + 1) * t - s);  // ���]�̓���
}
//===================================
// 
//===================================
float CEasing::EaseOutBack(float t)
{
	const float s = 0.70158f;  // ��������x����
	t -= 1;
	return (t * t * ((s + 1) * t + s) + 1);  // ���]�̓���
}
//===================================
// 
//===================================
float CEasing::EaseInOutBack(float t)
{
	const float s = 0.70158f * 1.525f;  // ��������x�����̒���

	if (t < 0.5f)
	{
		t *= 2;
		return 0.5f * (t * t * ((s + 1) * t - s));  // �O���͔��]�Ɖ���
	}
	else
	{
		t = t * 2 - 2;
		return 0.5f * (t * t * ((s + 1) * t + s) + 2);  // �㔼�͔��]�ƌ���
	}

}

//===================================
// 
//===================================
float CEasing::EaseInElastic(float t)
{
	if (t == 0)
	{
		return 0;  // �J�n���_
	}
	if (t == 1)
	{
		return 1;  // �I�����_
	}
	const float p = 0.3f;  // �U������
	const float s = p / 4;  // �U���̋���

	return (float)(-(pow(2, 10 * (t -= 1)) * sin((t - s) * (2 * D3DX_PI) / p)));  // �U���̓���
}
//===================================
// 
//===================================
float CEasing::EaseOutElastic(float t)
{
	if (t == 0)
	{
		return 0;  // �J�n���_
	}
	if (t == 1)
	{
		return 1;  // �I�����_
	}

	const float p = 0.3f;  // �U������
	const float s = p / 4;  // �U���̋���

	return (float)(pow(2, -10.0f * t) * sin((t - s) * (2 * D3DX_PI) / p) + 1);  // �U���̓���

}
//===================================
// 
//===================================
float CEasing::EaseInOutElastic(float t)
{
	if (t == 0)
	{
		return 0;  // �J�n���_
	}
	if (t == 1)
	{
		return 1;  // �I�����_
	}
	const float p = 0.3f * 1.5f;  // �U������
	const float s = p / 4;  // �U���̋���

	if (t < 0.5f)
	{
		return (float)(-0.5f * (pow(2, 20 * t - 10) * sin((20 * t - 11.125f) * (2 * D3DX_PI) / p)));
	}

	return (float)(pow(2, -20 * t + 10) * sin((20 * t - 11.125f) * (2 * D3DX_PI) / p) * 0.5f + 1);

}

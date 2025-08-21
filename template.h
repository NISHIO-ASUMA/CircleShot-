//================================
//
// �ėp�����֐� [ template.h ]
// Author : Asuma Nishio
//
//================================

#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

//*********************************
// �}�N����`
//*********************************
#define VALUE_FLOAT (2.0f)

//*********************************
// �͈͓��v�Z�֐�
//*********************************
template <class T>T Clump(const T t, const T min, const T max)
{
	if (t > max) return max; // ��������������ݒ�
	if (t < min) return min; // �����ȉ��Ȃ牺���ݒ�
	return t;
}

//*********************************
// ���[�v�l�v�Z�֐�
//*********************************
template <class T>T Wrap(const T t, const T min, const T max)
{
	if (t > max) return min; // �����������ŏ��l��
	if (t < min) return max; // �����ȉ��Ȃ�ő�l��
	return t;
}

//*********************************
// �p�x���K���v�Z
//*********************************
template <class T> T NormalAngle(T Angle)
{
	// �p�x�̐��K������
	if (Angle > D3DX_PI) Angle -= D3DX_PI * VALUE_FLOAT;
	if (Angle < D3DX_PI) Angle += D3DX_PI * VALUE_FLOAT;
	return Angle;
}
#endif // !_TEMPLETE_H_

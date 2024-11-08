/*
* @file		MeshCommonProcessing.cpp
* @brief	���b�V���̋��ʏ���
* @author	Morita
* @date		2024/07/30
*/

#include "pch.h"

#include"MeshCommonProcessing.h"

MeshCommonProcessing::MeshCommonProcessing()
{
}

MeshCommonProcessing::~MeshCommonProcessing()
{
}

bool MeshCommonProcessing::CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& playerPos, const float& playerLength)
{
	//		���b�V���̍ő�̕ӂ̒��������߂�
	float meshLength = std::max((vertex[0] - vertex[1]).Length(),
		std::max((vertex[0] - vertex[2]).Length(),
			(vertex[1] - vertex[2]).Length()));

	//		���b�V���̒��S�_�����߂�
	DirectX::SimpleMath::Vector3 m_centerPoint = (vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		�v���C���[�ƃ��b�V���̒��S�̍��W�����b�V���̒����ƃv���C���[�̃��C�̒�����菬������
	if ((m_centerPoint - playerPos).Length() <= meshLength + playerLength)
	{
		//		�������Ă���
		return true;
	}

	//		�������Ă��Ȃ�
	return false;
}

bool MeshCommonProcessing::OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& rayStart, const DirectX::SimpleMath::Vector3& rayEnd,
	const DirectX::SimpleMath::Vector3& normalize, DirectX::SimpleMath::Vector3* hitPoint)
{
	//		�O�p�`�̒��S�����߂�
	DirectX::SimpleMath::Vector3 center =
		(vertex[0] + vertex[1] + vertex[2]) / 3;

	//		���C�̕����Ɍ����Ă���x�N�g�����o��
	DirectX::SimpleMath::Vector3 velocityS = rayStart - center;
	DirectX::SimpleMath::Vector3 velocityE = rayEnd - center;

	//		���ς����
	float dotS = normalize.Dot(velocityS);
	float dotE = normalize.Dot(velocityE);

	//		�l���O�ȉ��̏ꍇ���������Ȃ�
	if (dotS * dotE <= 0)
	{
		//		���ʏ�̓_�����߂�
		float m = abs(dotS);
		float n = abs(dotE);

		//		�������Ă���|�C���g
		*hitPoint = (rayStart * n + rayEnd * m) / (m + n);

		//		�܂܂�Ă���
		return true;
	}

	//		�܂܂�Ă��Ȃ�
	return false;
}

bool MeshCommonProcessing::InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& normalize, const DirectX::SimpleMath::Vector3& hitPoint)
{
	for (int i = 0; i < 3; ++i)
	{
		//		�����������W�Ɍ������x�N�g��
		DirectX::SimpleMath::Vector3 hitVelocity = hitPoint - vertex[i];

		//		�ʂ̒��_�Ɍ������x�N�g��
		DirectX::SimpleMath::Vector3 meshVelocity = vertex[(i + 2) % 3] - vertex[i];

		//		�O�ς����߂�
		DirectX::SimpleMath::Vector3 cross = hitVelocity.Cross(meshVelocity);

		//		���K��
		cross.Normalize();

		//		�@���ƊO�ς̓��ς����
		float d = normalize.Dot(cross);

		//		0�ȉ��̏ꍇ�O�p�`�̊O���ɂ���
		if (d < 0)
		{
			//		�O��
			return false;
		}
	}

	//		����
	return true;
}

bool MeshCommonProcessing::PlayerObjectDirection(ObjectMesh* objectMesh,
	DirectX::SimpleMath::Vector3 playerPosition, int index)
{
	//		�v���C���[�ƃ��b�V���̋���
	float length = (objectMesh->GetMeshCenter()[index] - playerPosition).Length();

	if (length - 7.0f < objectMesh->GetMesnLength()[index])
	{
		return true;
	}

	return false;
}
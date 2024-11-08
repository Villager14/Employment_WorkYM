/*
* @file		BackGroundObjectInformation.h
* @brief	�w�i�I�u�W�F�N�g�̏��
* @author	Morita
* @date		2024/06/05
*/

#include "pch.h"

#include "BackGroundObjectInformation.h"

BackGroundObjectInformation::BackGroundObjectInformation()
{
}

BackGroundObjectInformation::~BackGroundObjectInformation()
{
}

void BackGroundObjectInformation::Create(std::vector<ObjectMesh*> mesh,
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	for (int i = 0, max = static_cast<int>(mesh.size()); i < max; ++i)
	{
		for (int j = 0, size = static_cast<int>(mesh[i]->GetObjectMesh().size());
			j < size; ++j)
		{
			float maxX = mesh[i]->GetMeshCenter()[j].x + mesh[i]->GetMesnLength()[j] + MAX_LENGTH;
			float maxZ = mesh[i]->GetMeshCenter()[j].z + mesh[i]->GetMesnLength()[j] + MAX_LENGTH;
			float minX = mesh[i]->GetMeshCenter()[j].x - mesh[i]->GetMesnLength()[j] - MAX_LENGTH;
			float minZ = mesh[i]->GetMeshCenter()[j].z - mesh[i]->GetMesnLength()[j] - MAX_LENGTH;

			RandomObjectPosition(maxX, minX, maxZ, minZ, mesh, wirePosition);
		}
	}

	for (int i = 0; i < wirePosition.size(); ++i)
	{
		float maxX = wirePosition[i].x + 20.0f + MAX_LENGTH;
		float maxZ = wirePosition[i].z + 20.0f + MAX_LENGTH;
		float minX = wirePosition[i].x - 20.0f - MAX_LENGTH;
		float minZ = wirePosition[i].z - 20.0f - MAX_LENGTH;

		RandomObjectPosition(maxX, minX, maxZ, minZ, mesh, wirePosition);
	}
}

bool BackGroundObjectInformation::ChackNormalize(DirectX::SimpleMath::Vector3 normalize)
{
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) >= 0.5f)
	{
		return true;
	}

	return false;
}

/*
*	���b�V�������W���w�i�I�u�W�F�N�g����΂ɒu���Ȃ��ꍇ��z�肵100�񗐐�����
*	���W�����܂�Ȃ������ꍇ�������s��Ȃ�
*/
void BackGroundObjectInformation::RandomObjectPosition
(float maxX, float minX, float maxZ, float minZ,
	std::vector<ObjectMesh*> mesh, 
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	int dot = 0;

	for (int j = 0; j < 20; ++j)
	{
		DirectX::SimpleMath::Vector3 randomPosition = DirectX::SimpleMath::Vector3(LibrarySingleton::GetInstance()->Random(minX, maxX),
			0.0f, LibrarySingleton::GetInstance()->Random(minZ, maxZ));

		if (ObjectMeshLength(randomPosition, mesh, wirePosition))
		{
			randomPosition.y = LibrarySingleton::GetInstance()->Random(-500.0f, -400.0f);

			m_objectPosition.push_back(randomPosition);

			//		�I�u�W�F�N�g�̉�]���쐬����
			ObjectCreateRotation();
		}
		else
		{
			j--;
			dot++;
		}

		//		����10��ȏ�ɂȂ�����I�u�W�F�N�g��u���Ȃ��Ƃ݂Ȃ�
		if (dot > 10)
		{
			break;
		}
	}
}

bool BackGroundObjectInformation::ObjectMeshLength(DirectX::SimpleMath::Vector3 randomPosition,
	std::vector<ObjectMesh*> mesh, const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	for (int i = 0, max = static_cast<int>(mesh.size()); i < max; ++i)
	{
		for (int j = 0; j < mesh[i]->GetObjectMesh().size(); ++j)
		{
			if ((DirectX::SimpleMath::Vector3(mesh[i]->GetMeshCenter()[j].x,
				0.0f, mesh[i]->GetMeshCenter()[j].z) - randomPosition).Length() <=
				mesh[i]->GetMesnLength()[j] + NOT_EXSIT_LENGTH)
			{
				return false;
			}
		}
	}

	for (int i = 0, max = static_cast<int>
		(wirePosition.size()); i < max; ++i)
	{
		if ((DirectX::SimpleMath::Vector3(wirePosition[i].x, 0.0f, wirePosition[i].z)
			- randomPosition).Length() < 150.0f)
		{
			return false;
		}
	}

	for (int i = 0, max = static_cast<int>
		(m_objectPosition.size()); i < max; ++i)
	{
		//		�����������̏ꍇ���������Ȃ�
		if ((DirectX::SimpleMath::Vector3(m_objectPosition[i].x , 0.0f, m_objectPosition[i].z)
			- randomPosition).Length() < 150.0f)
		{
			return false;
		}
	}

	return true;
}

void BackGroundObjectInformation::ObjectCreateRotation()
{
	m_objectRotation.push_back(DirectX::SimpleMath::Vector3(
		LibrarySingleton::GetInstance()->Random(-10.0f, 10.0f),
		LibrarySingleton::GetInstance()->Random(0.0f, 360.0f),
		LibrarySingleton::GetInstance()->Random(-10.0f, 10.0f)
	));

	m_objectQuaternion.push_back(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		{ DirectX::XMConvertToRadians(LibrarySingleton::GetInstance()->Random(-5.0f, 5.0f)),
		  DirectX::XMConvertToRadians(LibrarySingleton::GetInstance()->Random(0.0f, 360.0f)),
		  DirectX::XMConvertToRadians(LibrarySingleton::GetInstance()->Random(-5.0f, 5.0f))}));
}

void BackGroundObjectInformation::Finalize()
{
	m_objectPosition.clear();
	m_objectQuaternion.clear();
	m_objectRotation.clear();
	m_objectPosition.shrink_to_fit();
	m_objectQuaternion.shrink_to_fit();
	m_objectRotation.shrink_to_fit();
}


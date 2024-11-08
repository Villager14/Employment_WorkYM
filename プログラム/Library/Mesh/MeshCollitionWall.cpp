/*
* @file		MeshCollitionWall.cpp
* @brief	���b�V���̓����蔻���
* @author	Morita
* @date		2024/04/28
*/

#include "pch.h"

#include "MeshCollitionWall.h"

#include "MeshCollitionManager.h"

MeshCollitionWall::MeshCollitionWall(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager)
{
}

MeshCollitionWall::~MeshCollitionWall()
{
}

std::vector<DirectX::SimpleMath::Vector2> MeshCollitionWall::WallCollition(ObjectMesh* objectMesh,
	const DirectX::SimpleMath::Vector3& playerPosition, float height)
{
	m_playerPosition = playerPosition;

	//		0�ȊO�̎��폜����
	if (m_normalize.size() != 0) m_normalize.clear();

	m_wallHitJudgement = false;

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		ObjectCollider(objectMesh, i, height);
	}

	//		0�ȊO�̎��폜����
	if (m_moveVelocity.size() != 0) m_moveVelocity.clear();

	//		�ǂƓ������Ă���ꍇ
	if (m_wallHitJudgement)
	{
		m_moveVelocity.push_back({ m_playerPosition.x, m_playerPosition.z });
	}

	return m_moveVelocity;
}

void MeshCollitionWall::ObjectCollider(ObjectMesh* objectMesh, int index, float height)
{
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		�ǂ��ǂ������f����
		if (!WallJudgement(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];

		//		�J�������̍����𑫂�
		height += 0.5f;

		//		�~�̓����蔻��
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, m_playerPosition, height)) continue;

		//		�ǂ̍����̓����蔻��
		if (!WallHeight(vertex, height)) continue;

		//		���C�̊J�n�n�_
		m_rayStart = m_playerPosition;

		//		�e�X�g
		m_rayStart.y = RayY(vertex, m_playerPosition, height);

		//m_rayStart.y = std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y));

		//m_rayStart.y += 0.01f;

		//m_rayStart.y += 0.5f;

		if (m_rayStart.y > m_playerPosition.y + height)
		{
			continue;
		}

		m_rayEnd = m_rayStart;

		m_rayEnd += -objectMesh->GetObjectMesh()[index][i].m_normalVector * 2.0f;

		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
		{
			//		�ђʎ��̏���

			//		�ߋ��̍��W�����C�̊J�n�ʒu�ɂ���
			m_rayStart = m_pastPosition;

			//		���ꕽ�ʏ�ɂ��邩�ǂ���
			if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
				objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_hitPoint))
			{
				continue;
			}
			else
			{
				//		���b�V���̎O�p�`�̓������ǂ���
				if (!m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
					objectMesh->GetObjectMesh()[index][i].m_normalVector,
					m_hitPoint)) continue;

				m_playerPosition.x = m_hitPoint.x + objectMesh->GetObjectMesh()[index][i].m_normalVector.x * 2.0f;
				m_playerPosition.z = m_hitPoint.z + objectMesh->GetObjectMesh()[index][i].m_normalVector.z * 2.0f;

				m_normalize.push_back(objectMesh->GetObjectMesh()[index][i].m_normalVector);

				m_wallHitJudgement = true;
			}
		}
		else
		{

			//		���b�V���̎O�p�`�̓������ǂ���
			if (!m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
				objectMesh->GetObjectMesh()[index][i].m_normalVector,
				m_hitPoint)) continue;

			//		�X�̒��ɂ���ꍇ�������Ă���
			if (!Extrusion(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

			//		�������Ă���
			m_wallHitJudgement = true;
		}
	}
}

bool MeshCollitionWall::WallJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		������̖@���ɑ΂���+-45�x�̂��͕̂ǂƂ���
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) >= 0.5f ||
		DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).Dot(normalize) <= -0.5f)
	{
		//		�ǂł͂Ȃ�
		return false;
	}

	return true;
}

bool MeshCollitionWall::WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height)
{
	//		�v���C���[�����b�V���̍������ɂ��Ȃ��ꍇ���������Ȃ�
	if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) <= m_playerPosition.y + 0.3f  ||
		std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) >= m_playerPosition.y + height)
	{
		//		�ǂ̍����O
		return false;
	}

	//		�ǂ̍�����
	return true;
}

bool MeshCollitionWall::Extrusion(const DirectX::SimpleMath::Vector3& normalize)
{
	//		���������|�C���g�ƃv���C���[�̍��W�̒���
	float length = (m_rayStart - m_hitPoint).Length();

	//		�������v���C���[�̔��a���傫����Ώ��������Ȃ�
	if (length > 2.0f)
	{
		return false;
	}

	//		�@����񎟌��ɂ���
	DirectX::SimpleMath::Vector2 normalizeV2 = { normalize.x, normalize.z };
	//		���K������
	normalizeV2.Normalize();

	//		�l�������ȏ�ɂȂ�Ȃ��悤�ɂ���
	float change = Library::Clamp(length, 0.0f, 2.0f);

	change *= 0.5f;

	//		�ω���
	normalizeV2 *= Library::Lerp(2.0f, 0.0f, change);

	//		�߂荞�񂾕��ړ�������
	m_playerPosition.x += normalizeV2.x;
	m_playerPosition.z += normalizeV2.y;

	m_normalize.push_back(normalize);

	return true;
}

std::vector<DirectX::SimpleMath::Vector3>& MeshCollitionWall::WallWalk
(ObjectMesh* objectMesh, const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		�T�C�Y���O�ł͂Ȃ����폜����
	if (m_hitpp.size() != 0) m_hitpp.clear();

	for (int i = 0, max = static_cast<int>(objectMesh->GetObjectMesh().size()); i < max; ++i)
	{
		if (!m_meshCollitionManager->GetCommon()->PlayerObjectDirection(objectMesh, playerPosition, i)) continue;

		WallWalkCollider(objectMesh, playerPosition, i);
	}

	if (m_hitpp.size() == 1)
	{
		DirectX::SimpleMath::Vector3 pplayerPosition = { m_meshCollitionManager->GetWallWalkNormalize().x,
			0.0f, m_meshCollitionManager->GetWallWalkNormalize().z };

		pplayerPosition *= 2.0f;

		m_hitpp[0] += pplayerPosition;
	}

	return m_hitpp;
}

void MeshCollitionWall::WallWalkCollider(ObjectMesh* objectMesh,
										const DirectX::SimpleMath::Vector3& playerPosition,
										int index)
{
	//		���̒l����@�����쐬����
	m_meshCollitionManager->GetWallWalkNormalize();

	DirectX::SimpleMath::Vector2 normalize =
	{ m_meshCollitionManager->GetWallWalkNormalize().x,
		m_meshCollitionManager->GetWallWalkNormalize().z };

	normalize.Normalize();

	normalize *= -1;

	//		���C�̊J�n
	DirectX::SimpleMath::Vector3 rayStart = playerPosition;

	//		���C�̏I��
	DirectX::SimpleMath::Vector3 rayEnd = playerPosition;

	normalize *= 3.0f;

	rayEnd += {normalize.x, 0.0f, normalize.y};

	//		���_
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetObjectMesh()[index].size(); ++i)
	{
		//		�ǂ��ǂ������f����
		if (!WallJudgement(objectMesh->GetObjectMesh()[index][i].m_normalVector)) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetObjectMesh()[index][i].m_vertex[0];
		vertex[1] = objectMesh->GetObjectMesh()[index][i].m_vertex[1];
		vertex[2] = objectMesh->GetObjectMesh()[index][i].m_vertex[2];

		//		�v���C�[�̐L����菬�����ꍇ���������Ȃ�
		if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) - std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) < 7.0f)
		{
			continue;
		}

		//		�~�̓����蔻�肪�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
		if (!m_meshCollitionManager->GetCommon()->CollitionCC(vertex, rayStart, 2.0f))continue;

		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->GetCommon()->OnTheSamePlane(vertex, rayStart, rayEnd,
			objectMesh->GetObjectMesh()[index][i].m_normalVector, &m_wallWalkHitPoint)) continue;

		//		���b�V���̎O�p�`�̓������ǂ���
		if (m_meshCollitionManager->GetCommon()->InsideTriangle(vertex,
			objectMesh->GetObjectMesh()[index][i].m_normalVector,
			m_wallWalkHitPoint))
		{
			//		�������Ă��镔����ǉ�����
			m_hitpp.push_back(m_wallWalkHitPoint);
		}
	}
}

bool MeshCollitionWall::LinePointHit(
	DirectX::SimpleMath::Vector3 point,
	DirectX::SimpleMath::Vector3 lineA,
	DirectX::SimpleMath::Vector3 lineB,
	DirectX::SimpleMath::Vector3* ans)
{
	DirectX::SimpleMath::Vector3 lineAB = lineB - lineA;
	DirectX::SimpleMath::Vector3 linePA = point - lineA;

	float t = linePA.Dot(lineAB) / lineAB.LengthSquared();

	//		���̌����̊O�ɍs�����ꍇ���������Ȃ�
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}

	*ans = lineA + t * lineAB;

	return true;
}

float MeshCollitionWall::RayY(std::vector<DirectX::SimpleMath::Vector3> vertex,
							  DirectX::SimpleMath::Vector3 position,
							  float height)
{
	std::vector<DirectX::SimpleMath::Vector3> hitLine;
	std::vector<DirectX::SimpleMath::Vector3> centerDirection;

	DirectX::SimpleMath::Vector3 point = position;

	DirectX::SimpleMath::Vector3 ans;

	DirectX::SimpleMath::Vector3 center = (vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	for (int i = 0; i < vertex.size(); ++i)
	{
		int val = i + 1;

		if (i == 2)
		{
			val = 0;
		}

		if (LinePointHit(point, vertex[i], vertex[val], &ans))
		{
			DirectX::SimpleMath::Vector3 direction = center - ans;

			direction.Normalize();

			centerDirection.push_back(direction);

			hitLine.push_back(ans);
		}
	}
	
	if (hitLine.size() == 2)
	{
		return PerpendicularPointSecond(hitLine[0].y,
										hitLine[1].y,
										position.y,
										position.y + height);
	}

	if (hitLine.size() == 1)
	{
		return hitLine[0].y;
	}

	return position.y;
}

float MeshCollitionWall::PerpendicularPointSecond(
									float point1,
									float point2,
									float playerUnder,
									float playerHeight)
{
	//		�I�u�W�F�N�g(��) > �v���C��(��)
	if (std::max(point1, point2) > playerHeight)
	{
		//		�I�u�W�F�N�g(��) < �v���C��(��)
		if (std::min(point1, point2) < playerUnder)
		{
			//		�v���C���̒��S�̍���
			return (playerUnder + playerHeight) / 2.0f;
		}
		//		�I�u�W�F�N�g(��) > �v���C��(��)
		else
		{
			//		�I�u�W�F�N�g(��)�ƃv���C��(��)�̒��S�̍���
			return (std::min(point1, point2) + playerHeight) / 2.0f;
		}
	}
	//		�I�u�W�F�N�g(��) < �v���C��(��)
	else
	{
		//		�I�u�W�F�N�g(��) < �v���C��(��)
		if (std::min(point1, point2) < playerUnder)
		{
			//		�I�u�W�F�N�g(��)�ƃv���C��(��)�̒��S�̍���
			return (std::max(point1, point2) + playerUnder) / 2.0f;
		}
		//		�I�u�W�F�N�g(��) > �v���C��(��)
		else
		{
			//		�I�u�W�F�N�g�̒��S����
			return (point1 + point2) / 2.0f;
		}
	}
}

void MeshCollitionWall::Finalize()
{
	m_hitpp.clear();
	m_hitpp.shrink_to_fit();
	m_normalize.clear();
	m_normalize.shrink_to_fit();
	m_moveVelocity.clear();
	m_moveVelocity.shrink_to_fit();
}


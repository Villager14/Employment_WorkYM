
#pragma once

#include "pch.h"

#include <vector>

struct Triangle
{
	//		���_
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		���_�C���f�b�N�X
	std::vector<int> m_vertexIndex;

	//		�@��
	DirectX::SimpleMath::Vector3 m_normalVector;
};
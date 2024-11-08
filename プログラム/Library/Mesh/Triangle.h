
#pragma once

#include "pch.h"

#include <vector>

struct Triangle
{
	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		頂点インデックス
	std::vector<int> m_vertexIndex;

	//		法線
	DirectX::SimpleMath::Vector3 m_normalVector;
};
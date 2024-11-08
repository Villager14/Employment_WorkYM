/*
* @file		LeadMesh.cpp
* @brief	メッシュの読み込み
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "LeadMesh.h"

#include <fstream>

#include <Effects.h>

#include <algorithm>

LeadMesh::LeadMesh()
	:
	m_vertexCount(0)
{
	//		メッシュの整理クラスの生成
	m_origanization = std::make_unique<MeshOrganization>();
}

LeadMesh::~LeadMesh()
{
}

std::vector<Triangle> LeadMesh::Lead
							(const wchar_t* filePath)
{
	//		配列をリセット
	m_triangle.clear();

	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex;

	//		頂点インデックス
	std::vector<int> vertexIndex;

	//		ファイルを開く
	std::ifstream ifs(filePath);

	std::string str;

	while (std::getline(ifs, str))
	{
		//		頂点の場合
		if (str[0] == 'v' && str[1] == ' ')
		{
			DirectX::SimpleMath::Vector3 val;

			//		ファイルから受けとった値をfloatへ変換&代入する
			sscanf_s(str.data(), "v %f %f %f", &val.x, &val.y, &val.z);

			//		頂点を受け取る
			vertex.push_back(val);

			//		頂点を受け取る
			m_vertex.push_back(val);

			//		頂点の数を増やす
			m_vertexCount++;
		}

		//		インデックスの場合
		if (str[0] == 'f')
		{
			int a, b, c;

			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);

			if (a != b && a != c && b != c)
			{
				vertexIndex.push_back(a - 1);
				vertexIndex.push_back(b - 1);
				vertexIndex.push_back(c - 1);

				m_vertexIndex.push_back(a - 1);
				m_vertexIndex.push_back(b - 1);
				m_vertexIndex.push_back(c - 1);
			}
		}
	}

	//		ファイルを閉じる
	ifs.close();

	m_triangle = m_origanization->Organization(vertex, vertexIndex);

	return std::move(m_triangle);
}

void LeadMesh::Clear()
{
	m_triangle.clear();
	m_vertex.clear();
	m_vertexIndex.clear();
}

/*
* @file		DrawMesh.cpp
* @brief	ƒƒbƒVƒ…‚Ì•`‰æ
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "DrawMesh.h"

#include "Common/DebugDraw.h"

DrawMesh::DrawMesh()
{
}

DrawMesh::~DrawMesh()
{
}

void DrawMesh::StaticRender(ObjectMesh* objectMesh)
{
	LibrarySingleton::GetInstance()->
		GetVertexPositionColor()->Begin();

	std::vector<DirectX::SimpleMath::Vector3> vertex;

	for (int i = 0; i < objectMesh->GetObjectMesh().size(); ++i)
	{
		for (int j = 0; j < objectMesh->GetObjectMesh()[i].size(); ++j)
		{
			vertex.push_back(objectMesh->GetObjectMesh()[i][j].m_vertex[0]);
			vertex.push_back(objectMesh->GetObjectMesh()[i][j].m_vertex[1]);
			vertex.push_back(objectMesh->GetObjectMesh()[i][j].m_vertex[2]);

			//		ƒƒbƒVƒ…‚Ì•`‰æ
			DX::DrawTriangle(LibrarySingleton::GetInstance()->
				GetVertexPositionColor(),
				vertex[0], vertex[1], vertex[2],
				DirectX::Colors::Red);

			//		–@ü‚Ì•`‰æ
			NormalizeRender(vertex,
				objectMesh->GetObjectMesh()[i][j].m_normalVector);

			vertex.clear();
		}


	}

	LibrarySingleton::GetInstance()->
		GetVertexPositionColor()->End();


	/*
	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		vertex.push_back(objectMesh->GetVertexPosition(i, 0));
		vertex.push_back(objectMesh->GetVertexPosition(i, 1));
		vertex.push_back(objectMesh->GetVertexPosition(i, 2));

		//		ƒƒbƒVƒ…‚Ì•`‰æ
		DX::DrawTriangle(LibrarySingleton::GetInstance()->
						 GetVertexPositionColor(), 
						 vertex[0], vertex[1], vertex[2],
						 DirectX::Colors::Red);
						
		//		–@ü‚Ì•`‰æ
		NormalizeRender(vertex,
			objectMesh->GetNormalizePosition(i));

		vertex.clear();
	}

	LibrarySingleton::GetInstance()->
		GetVertexPositionColor()->End();
		*/
}

void DrawMesh::DaynamicRender(ObjectMesh* objectMesh,
							const DirectX::SimpleMath::Matrix& world)
{
	UNREFERENCED_PARAMETER(objectMesh);
	UNREFERENCED_PARAMETER(world);

	LibrarySingleton::GetInstance()->
		GetVertexPositionColor()->Begin();

	std::vector<DirectX::SimpleMath::Vector3> vertex;

	//for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	//{
	//	vertex.push_back(DirectX::SimpleMath::Vector3::Transform(objectMesh->GetVertexPosition(i, 0), world));
	//	vertex.push_back(DirectX::SimpleMath::Vector3::Transform(objectMesh->GetVertexPosition(i, 0), world));
	//	vertex.push_back(DirectX::SimpleMath::Vector3::Transform(objectMesh->GetVertexPosition(i, 0), world));

	//	//		ƒƒbƒVƒ…‚Ì•`‰æ
	//	DX::DrawTriangle(LibrarySingleton::GetInstance()->
	//		GetVertexPositionColor(),
	//		vertex[0], vertex[1], vertex[2],
	//		DirectX::Colors::Red);

	//	//		–@ü‚Ì•`‰æ
	//	NormalizeRender(vertex,
	//		objectMesh->GetNormalizePosition(i));

	//	vertex.clear();
	//}

	LibrarySingleton::GetInstance()->
		GetVertexPositionColor()->End();
}

void DrawMesh::DrawSphere(DirectX::SimpleMath::Vector3 center, float radian)
{
	DirectX::XMFLOAT3 center2 = static_cast<DirectX::XMFLOAT3>(center);
	
	const DirectX::XMVECTOR origin = DirectX::XMLoadFloat3(&center2);

	const DirectX::XMVECTOR xaxis = DirectX::XMVectorScale(DirectX::g_XMIdentityR0, radian);
	const DirectX::XMVECTOR yaxis = DirectX::XMVectorScale(DirectX::g_XMIdentityR1, radian);
	const DirectX::XMVECTOR zaxis = DirectX::XMVectorScale(DirectX::g_XMIdentityR2, radian);

	DirectX::SimpleMath::Vector4 color = { 0.0f, 1.0f, 0.0f, 1.0f };

	DX::DrawRing(LibrarySingleton::GetInstance()->
		GetVertexPositionColor(), origin, xaxis, zaxis, color);
	DX::DrawRing(LibrarySingleton::GetInstance()->
		GetVertexPositionColor(), origin, xaxis, yaxis, color);
	DX::DrawRing(LibrarySingleton::GetInstance()->
		GetVertexPositionColor(), origin, yaxis, zaxis, color);
}

void DrawMesh::NormalizeRender(
	const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& normalize)
{
	//		ŽOŠpŒ`‚Ì’†S
	DirectX::SimpleMath::Vector3 position =
		(vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		ŽOŠpŒ`‚Ì’†S@{@–@ü
	DirectX::SimpleMath::Vector3 positionNormalizeVelocity = position + normalize;

	DirectX::VertexPositionColor verts[3];

	//		ŽOŠpŒ`‚Ì’†S‚ð‘ã“ü‚·‚é
	verts[0].position = position;

	//		ŽOŠpŒ`‚Ì’†S + –@§‚ð‘ã“ü‚·‚é
	verts[1].position = positionNormalizeVelocity;

	//		–@ü‚Ì•`‰æ
	LibrarySingleton::GetInstance()->
		GetVertexPositionColor()
		->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, 2);
}

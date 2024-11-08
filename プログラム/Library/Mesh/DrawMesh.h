/*
* @file		DrawMesh.h
* @brief	メッシュの描画
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include "ObjectMesh.h"

class DrawMesh
{
public:

	//		コンストラクタ
	DrawMesh();

	//		デストラクタ
	~DrawMesh();
	
	//		静的描画
	void StaticRender(ObjectMesh* objectMesh);

	//		動的描画
	void DaynamicRender(ObjectMesh* objectMesh,
						const DirectX::SimpleMath::Matrix& world);

	/*
	*	円の描画
	* 
	*/
	void DrawSphere(DirectX::SimpleMath::Vector3 center, float radian);

	/*
	*	メッシュを描画する
	*
	*	@param	(index)		配列の番号
	*	@param	(vertex)	頂点
	*/
	void MeshRender(const int& index,
		const std::vector<DirectX::SimpleMath::Vector3>& vertex);

	/*
	*	法線を描画する
	*
	*	@param	(normalize)			法線
	*	@param	(vertex)			頂点
	*/
	void NormalizeRender(
		const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& normalize);
};
/*
* @file		MeshOrganization.h
* @brief	メッシュの整理
* @author	Morita
* @date		2024/09/18
*/

#pragma once

#include <vector>

#include "Triangle.h"

class MeshOrganization
{
public:

	//		コンストラクタ
	MeshOrganization();

	//		デストラクタ
	~MeshOrganization();

	std::vector<Triangle> Organization(
		const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const std::vector<int> vertexIndex);

private:

	std::vector<Triangle> CreateTrinangle(
		const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const std::vector<int> vertexIndex);

	void CreateNormalize();


	void ObjectInformation();

	bool Sort(int index);

	void AddCodNumber(int index);

	void AddObject();

	//		頂点インデックスの削除
	void ClearVertexIndex();

	//		半径を作成する
	void CreateRadius();

	/*
	*	オブジェクトの最大値
	*
	*	@param	(max)	最大値配列
	*	@return 最大値
	*/
	DirectX::SimpleMath::Vector3 ObjectMax(std::vector<DirectX::SimpleMath::Vector3> max);


	/*
	*	オブジェクトの最小値
	*
	*	@param	(min)	最小値値配列
	*	@return 最小値
	*/
	DirectX::SimpleMath::Vector3 ObjectMin(std::vector<DirectX::SimpleMath::Vector3> min);

	void Objectlength(DirectX::SimpleMath::Vector3 max, DirectX::SimpleMath::Vector3 min);

private:

	//		三角形情報
	std::vector<Triangle> m_triangle;

	//		メッシュ情報のコピー
	std::vector<Triangle> m_copytriangle;

	//		コードの番号
	std::vector<int> codNumber;

	//		オブジェクト
	std::unordered_map<int, std::vector<Triangle>> m_object;

	//		メッシュの長さ
	std::vector<float> m_meshLength;

	//		メッシュの中心
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;

public:

	/*
	*	メッシュの長さを受け取る
	*
	*	@return 長さ
	*/
	std::vector<float> GetMesnLength() { return m_meshLength; }

	//		オブジェクトメッシュを受け取る
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_object; }

	/*
	*	メッシュの中心を受け取る
	*
	*	@return 中心
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return  m_meshCenter; }

};
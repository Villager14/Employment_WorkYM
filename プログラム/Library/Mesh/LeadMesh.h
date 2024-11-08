/*
* @file		LeadMesh.h
* @brief	メッシュの読み込み
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include <vector>

#include "Triangle.h"

#include "MeshOrganization.h"

class LeadMesh
{
public:

	//		コンストラクタ
	LeadMesh();

	//		デストラクタ
	~LeadMesh();

	/*
	*	メッシュの読み込み
	* 
	*	@param	(fielPath)	ファイルパス
	*/
	std::vector<Triangle>
		Lead(const wchar_t* filePath);

	//		情報の削除
	void Clear();

private:

	//		メッシュの整理クラス	
	std::unique_ptr<MeshOrganization> m_origanization;

	//		三角メッシュの情報
	std::vector<Triangle> m_triangle;

	//		頂点の数
	int m_vertexCount;

	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		頂点インデックス
	std::vector<int> m_vertexIndex;
public:

	/*
	*	メッシュの長さを受け取る
	* 
	*	@return 長さ
	*/
	std::vector<float> GetMesnLength() { return m_origanization->GetMesnLength(); }

	//		オブジェクトメッシュを受け取る
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_origanization->GetObjectMesh(); }

	/*
	*	メッシュの中心を受け取る
	* 
	*	@return 中心
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return m_origanization->GetMeshCenter(); }

	/*
	*	頂点の数
	* 
	*	@return 数
	*/
	int GetVertexCount() { return m_vertexCount; }

	/*
	*	頂点を受け取る
	* 
	*	@return 頂点
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetVertex() { return m_vertex; }

	std::vector<int> GetVertexIndex() { return m_vertexIndex; }
};
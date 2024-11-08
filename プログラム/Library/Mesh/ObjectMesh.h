/*
* @file		ObjectMesh.h
* @brief	オブジェクトのメッシュ
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include <vector>

#include "Triangle.h"

#include "Library/Mesh/LeadMesh.h"

class ObjectMesh
{
public:

	//		コンストラクタ
	ObjectMesh();

	//		デストラクタ
	~ObjectMesh();

	//		初期化処理
	/*
	*	初期化処理
	* 
	*	@param	(filePath)	ファイルパス
	*/
	void Initialize(const wchar_t* filePath);

	/*
	*	静的な処理を行う(静的なオブジェクトの場合のみ呼ぶ)
	* 
	*	@param	(world)	ワールド行列
	*	@param	(move)	移動処理
	*/
	void StaticProcess(const DirectX::SimpleMath::Matrix& world,
					  const DirectX::SimpleMath::Vector3& move);

	//		終了処理
	void Finalize();

public:

	enum class ObjectType
	{
		Floor,
		Wall,
		Goal,
		DamageObject,
		SignboardObject,
		Null
	};

private:

	//		オブジェクトの種類
	ObjectType m_objectType;

	//		メッシュ情報の読み込み
	std::unique_ptr<LeadMesh> m_leadMesh;

	//		静的オブジェクトかどうか
	bool m_staticObjectJudgement;

	//		オブジェクトメッシュ
	std::unordered_map<int, std::vector<Triangle>> m_objectMesh;

	//		メッシュの長さ
	std::vector<float> m_meshLength;

	//		メッシュの中心
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;

public:

	/*
	*	静的なオブジェクトかどうか
	* 
	*	@return true : 静的なオブジェクト false : 動的なオブジェクト
	*/
	bool GetStaticObjectJudgement() { return m_staticObjectJudgement; }

	/*
	*	オブジェクトのタイプを設定する
	* 
	*	@param	(type)	オブジェクトのタイプ
	*/
	void SetObuectType(ObjectType type) { m_objectType = type; }

	/*
	*	オブジェクトのタイプを受け取る
	* 
	*	@return オブジェクトのタイプ
	*/
	const ObjectType& GetObjectType() { return m_objectType; }

	/*
	*	オブジェクトのメッシュ情報を受け取る
	* 
	*	@return オブジェクトメッシュ
	*/
	inline std::unordered_map<int, std::vector<Triangle>>& GetObjectMesh() { return m_objectMesh; }

	/*
	*	メッシュの長さを受け取る
	*
	*	@return 長さ
	*/
	std::vector<float> GetMesnLength() { return m_meshLength; }

	/*
	*	メッシュの中心を受け取る
	*
	*	@return 中心
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return m_meshCenter; }
};

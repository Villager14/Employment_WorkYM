/*
* @file		BackGroundObjectInformation.h
* @brief	背景オブジェクトの情報
* @author	Morita
* @date		2024/06/05
*/

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/LeadMesh.h"

class BackGroundObjectInformation
{
public:

	//		コンストラクタ
	BackGroundObjectInformation();

	//		デストラクタ
	~BackGroundObjectInformation();

	/*
	*	オブジェクトの座標の生成
	* 
	*	@param	(mesh)	オブジェクトのメッシュの情報のポインタ
	*/	
	void Create(std::vector<ObjectMesh*> mesh, 
		const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	/*
	*	メッシュの法線の情報から判断する
	* 
	*	@param	(normalize)	メッシュの法線
	*	@return 個の法線を使うかどうか
	*/
	bool ChackNormalize(DirectX::SimpleMath::Vector3 normalize);
	
	/*
	*	ランダムなオブジェクトの座標の処理
	* 
	*	@param	(maxX)	Xの最大距離
	*	@praam	(minX)	Xの最小距離
	*	@param	(maxZ)	Zの最大距離
	*	@param	(minZ)	Zの最小距離
	*/
	void RandomObjectPosition(float maxX, float minX, float maxZ, float minZ,
		std::vector<ObjectMesh*> mesh, const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	/*
	*	オブジェクトとメッシュの距離を計算する
	* 
	*	@param	(randomPosition)	オブジェクトの座標
	*/
	bool ObjectMeshLength(DirectX::SimpleMath::Vector3 randomPosition,
		std::vector<ObjectMesh*> mesh, const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	//		オブジェクトの回転を設定する
	void ObjectCreateRotation();

	void Finalize();

public:

	struct Vertex
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector2 texcoord;
	};

private:
	
	//		建物が存在しない距離
	const float NOT_EXSIT_LENGTH = 200.0f;

	//		建物が存在する最大距離
	const float MAX_LENGTH = 380.0f;

private:

	//		オブジェクトの座標
	std::vector<DirectX::SimpleMath::Vector3> m_objectPosition;

	//		オブジェクトの回転
	std::vector<DirectX::SimpleMath::Vector3> m_objectRotation;

	//		オブジェクトのクオータニオン
	std::vector<DirectX::SimpleMath::Quaternion> m_objectQuaternion;

public:

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectPosition() { return m_objectPosition; }

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectRotation() { return m_objectRotation; }

	const std::vector<DirectX::SimpleMath::Quaternion>& GetObjectQuaternion() { return m_objectQuaternion; }
};

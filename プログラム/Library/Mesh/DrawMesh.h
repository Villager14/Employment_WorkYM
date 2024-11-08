/*
* @file		DrawMesh.h
* @brief	���b�V���̕`��
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include "ObjectMesh.h"

class DrawMesh
{
public:

	//		�R���X�g���N�^
	DrawMesh();

	//		�f�X�g���N�^
	~DrawMesh();
	
	//		�ÓI�`��
	void StaticRender(ObjectMesh* objectMesh);

	//		���I�`��
	void DaynamicRender(ObjectMesh* objectMesh,
						const DirectX::SimpleMath::Matrix& world);

	/*
	*	�~�̕`��
	* 
	*/
	void DrawSphere(DirectX::SimpleMath::Vector3 center, float radian);

	/*
	*	���b�V����`�悷��
	*
	*	@param	(index)		�z��̔ԍ�
	*	@param	(vertex)	���_
	*/
	void MeshRender(const int& index,
		const std::vector<DirectX::SimpleMath::Vector3>& vertex);

	/*
	*	�@����`�悷��
	*
	*	@param	(normalize)			�@��
	*	@param	(vertex)			���_
	*/
	void NormalizeRender(
		const std::vector<DirectX::SimpleMath::Vector3>& vertex,
		const DirectX::SimpleMath::Vector3& normalize);
};
/*
* @file		LeadMesh.h
* @brief	���b�V���̓ǂݍ���
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

	//		�R���X�g���N�^
	LeadMesh();

	//		�f�X�g���N�^
	~LeadMesh();

	/*
	*	���b�V���̓ǂݍ���
	* 
	*	@param	(fielPath)	�t�@�C���p�X
	*/
	std::vector<Triangle>
		Lead(const wchar_t* filePath);

	//		���̍폜
	void Clear();

private:

	//		���b�V���̐����N���X	
	std::unique_ptr<MeshOrganization> m_origanization;

	//		�O�p���b�V���̏��
	std::vector<Triangle> m_triangle;

	//		���_�̐�
	int m_vertexCount;

	//		���_
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		���_�C���f�b�N�X
	std::vector<int> m_vertexIndex;
public:

	/*
	*	���b�V���̒������󂯎��
	* 
	*	@return ����
	*/
	std::vector<float> GetMesnLength() { return m_origanization->GetMesnLength(); }

	//		�I�u�W�F�N�g���b�V�����󂯎��
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_origanization->GetObjectMesh(); }

	/*
	*	���b�V���̒��S���󂯎��
	* 
	*	@return ���S
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return m_origanization->GetMeshCenter(); }

	/*
	*	���_�̐�
	* 
	*	@return ��
	*/
	int GetVertexCount() { return m_vertexCount; }

	/*
	*	���_���󂯎��
	* 
	*	@return ���_
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetVertex() { return m_vertex; }

	std::vector<int> GetVertexIndex() { return m_vertexIndex; }
};
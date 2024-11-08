/*
* @file		MeshOrganization.h
* @brief	���b�V���̐���
* @author	Morita
* @date		2024/09/18
*/

#pragma once

#include <vector>

#include "Triangle.h"

class MeshOrganization
{
public:

	//		�R���X�g���N�^
	MeshOrganization();

	//		�f�X�g���N�^
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

	//		���_�C���f�b�N�X�̍폜
	void ClearVertexIndex();

	//		���a���쐬����
	void CreateRadius();

	/*
	*	�I�u�W�F�N�g�̍ő�l
	*
	*	@param	(max)	�ő�l�z��
	*	@return �ő�l
	*/
	DirectX::SimpleMath::Vector3 ObjectMax(std::vector<DirectX::SimpleMath::Vector3> max);


	/*
	*	�I�u�W�F�N�g�̍ŏ��l
	*
	*	@param	(min)	�ŏ��l�l�z��
	*	@return �ŏ��l
	*/
	DirectX::SimpleMath::Vector3 ObjectMin(std::vector<DirectX::SimpleMath::Vector3> min);

	void Objectlength(DirectX::SimpleMath::Vector3 max, DirectX::SimpleMath::Vector3 min);

private:

	//		�O�p�`���
	std::vector<Triangle> m_triangle;

	//		���b�V�����̃R�s�[
	std::vector<Triangle> m_copytriangle;

	//		�R�[�h�̔ԍ�
	std::vector<int> codNumber;

	//		�I�u�W�F�N�g
	std::unordered_map<int, std::vector<Triangle>> m_object;

	//		���b�V���̒���
	std::vector<float> m_meshLength;

	//		���b�V���̒��S
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;

public:

	/*
	*	���b�V���̒������󂯎��
	*
	*	@return ����
	*/
	std::vector<float> GetMesnLength() { return m_meshLength; }

	//		�I�u�W�F�N�g���b�V�����󂯎��
	std::unordered_map<int, std::vector<Triangle>> GetObjectMesh() { return m_object; }

	/*
	*	���b�V���̒��S���󂯎��
	*
	*	@return ���S
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return  m_meshCenter; }

};
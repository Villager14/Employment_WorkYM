/*
* @file		ObjectMesh.h
* @brief	�I�u�W�F�N�g�̃��b�V��
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

	//		�R���X�g���N�^
	ObjectMesh();

	//		�f�X�g���N�^
	~ObjectMesh();

	//		����������
	/*
	*	����������
	* 
	*	@param	(filePath)	�t�@�C���p�X
	*/
	void Initialize(const wchar_t* filePath);

	/*
	*	�ÓI�ȏ������s��(�ÓI�ȃI�u�W�F�N�g�̏ꍇ�̂݌Ă�)
	* 
	*	@param	(world)	���[���h�s��
	*	@param	(move)	�ړ�����
	*/
	void StaticProcess(const DirectX::SimpleMath::Matrix& world,
					  const DirectX::SimpleMath::Vector3& move);

	//		�I������
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

	//		�I�u�W�F�N�g�̎��
	ObjectType m_objectType;

	//		���b�V�����̓ǂݍ���
	std::unique_ptr<LeadMesh> m_leadMesh;

	//		�ÓI�I�u�W�F�N�g���ǂ���
	bool m_staticObjectJudgement;

	//		�I�u�W�F�N�g���b�V��
	std::unordered_map<int, std::vector<Triangle>> m_objectMesh;

	//		���b�V���̒���
	std::vector<float> m_meshLength;

	//		���b�V���̒��S
	std::vector<DirectX::SimpleMath::Vector3> m_meshCenter;

public:

	/*
	*	�ÓI�ȃI�u�W�F�N�g���ǂ���
	* 
	*	@return true : �ÓI�ȃI�u�W�F�N�g false : ���I�ȃI�u�W�F�N�g
	*/
	bool GetStaticObjectJudgement() { return m_staticObjectJudgement; }

	/*
	*	�I�u�W�F�N�g�̃^�C�v��ݒ肷��
	* 
	*	@param	(type)	�I�u�W�F�N�g�̃^�C�v
	*/
	void SetObuectType(ObjectType type) { m_objectType = type; }

	/*
	*	�I�u�W�F�N�g�̃^�C�v���󂯎��
	* 
	*	@return �I�u�W�F�N�g�̃^�C�v
	*/
	const ObjectType& GetObjectType() { return m_objectType; }

	/*
	*	�I�u�W�F�N�g�̃��b�V�������󂯎��
	* 
	*	@return �I�u�W�F�N�g���b�V��
	*/
	inline std::unordered_map<int, std::vector<Triangle>>& GetObjectMesh() { return m_objectMesh; }

	/*
	*	���b�V���̒������󂯎��
	*
	*	@return ����
	*/
	std::vector<float> GetMesnLength() { return m_meshLength; }

	/*
	*	���b�V���̒��S���󂯎��
	*
	*	@return ���S
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetMeshCenter() { return m_meshCenter; }
};

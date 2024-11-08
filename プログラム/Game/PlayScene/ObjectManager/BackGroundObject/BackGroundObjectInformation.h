/*
* @file		BackGroundObjectInformation.h
* @brief	�w�i�I�u�W�F�N�g�̏��
* @author	Morita
* @date		2024/06/05
*/

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/LeadMesh.h"

class BackGroundObjectInformation
{
public:

	//		�R���X�g���N�^
	BackGroundObjectInformation();

	//		�f�X�g���N�^
	~BackGroundObjectInformation();

	/*
	*	�I�u�W�F�N�g�̍��W�̐���
	* 
	*	@param	(mesh)	�I�u�W�F�N�g�̃��b�V���̏��̃|�C���^
	*/	
	void Create(std::vector<ObjectMesh*> mesh, 
		const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	/*
	*	���b�V���̖@���̏�񂩂画�f����
	* 
	*	@param	(normalize)	���b�V���̖@��
	*	@return �̖@�����g�����ǂ���
	*/
	bool ChackNormalize(DirectX::SimpleMath::Vector3 normalize);
	
	/*
	*	�����_���ȃI�u�W�F�N�g�̍��W�̏���
	* 
	*	@param	(maxX)	X�̍ő勗��
	*	@praam	(minX)	X�̍ŏ�����
	*	@param	(maxZ)	Z�̍ő勗��
	*	@param	(minZ)	Z�̍ŏ�����
	*/
	void RandomObjectPosition(float maxX, float minX, float maxZ, float minZ,
		std::vector<ObjectMesh*> mesh, const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	/*
	*	�I�u�W�F�N�g�ƃ��b�V���̋������v�Z����
	* 
	*	@param	(randomPosition)	�I�u�W�F�N�g�̍��W
	*/
	bool ObjectMeshLength(DirectX::SimpleMath::Vector3 randomPosition,
		std::vector<ObjectMesh*> mesh, const std::vector<DirectX::SimpleMath::Vector3>& wirePosition);

	//		�I�u�W�F�N�g�̉�]��ݒ肷��
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
	
	//		���������݂��Ȃ�����
	const float NOT_EXSIT_LENGTH = 200.0f;

	//		���������݂���ő勗��
	const float MAX_LENGTH = 380.0f;

private:

	//		�I�u�W�F�N�g�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_objectPosition;

	//		�I�u�W�F�N�g�̉�]
	std::vector<DirectX::SimpleMath::Vector3> m_objectRotation;

	//		�I�u�W�F�N�g�̃N�I�[�^�j�I��
	std::vector<DirectX::SimpleMath::Quaternion> m_objectQuaternion;

public:

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectPosition() { return m_objectPosition; }

	const std::vector<DirectX::SimpleMath::Vector3>& GetObjectRotation() { return m_objectRotation; }

	const std::vector<DirectX::SimpleMath::Quaternion>& GetObjectQuaternion() { return m_objectQuaternion; }
};

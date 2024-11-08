/*
* @file		BackGroundObject.cpp
* @brief	�w�i�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/23
*/

#include "BackGroundObjectInformation.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Instancing.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"
class BackGroundObject
{
public:

	//		�R���X�g���N�^
	BackGroundObject(ObjectManager* objectManager);

	//		�f�X�g���N�^
	~BackGroundObject();

	//		����������
	void Initialize(std::vector<ObjectMesh*> mesh,
		const std::vector<DirectX::SimpleMath::Vector3>& m_wirePosition);

	//		�X�V����
	void Update();

	//		�`��I�u�W�F�N�g
	void Render(PostEffectFlag::Flag flag,
				PostEffectObjectShader* objectShader);

	//		�I������
	void Finalize();

private:

	std::unique_ptr<DirectX::Model> m_backGroundModel;

	//		���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//		���
	std::unique_ptr<BackGroundObjectInformation> m_information;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		�o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	//		�Q�[���}�l�[�W���[
	ObjectManager* m_objectManager;

	//		�C���X�^���V���O�`��
	std::unique_ptr<Instancing> m_instancing;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

public:

	/*
	*	�|�X�g�G�t�F�N�g�t���O
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectFlag* GetPostEffectFlag() { return m_postEffectFlag.get(); }
};

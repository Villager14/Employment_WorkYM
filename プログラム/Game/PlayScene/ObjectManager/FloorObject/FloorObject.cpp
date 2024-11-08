/*
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "FloorObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

#include <SpriteFont.h>

FloorObject::FloorObject(ObjectManager* objectManager)
	:
	m_floorModel{},
	m_objectManager(objectManager)
{
	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

FloorObject::~FloorObject()
{

}

void FloorObject::Initialize(ObjectInformation information)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		���f���̓ǂݍ���
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);
	
	m_floorModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
			}
		});

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		����������
	m_objectMesh->Initialize(oss2.str().c_str());

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(information.rotation.y));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(information.rotation.y)), information.position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Floor);

	// �s�N�Z���V�F�[�_�[�̍쐬
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	if (information.effectFlag)
	{
		//		�A���t�@�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);

		//		�u���[�����|����悤�ɂ���
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

		//		�ʏ�`�掞�ɂ��`�悷��悤�ɂ����
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

		//		�u���[���̐[�x�`��͕`�悵�Ȃ�
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

		//		�t�H�O�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	}
	else
	{
		//		�ʏ�`�������悤�ɂ���
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

		//		�u���[�����|����悤�ɂ���
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

		//		�u���[���̐[�x�`��͕`�悵�Ȃ�
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);

		//		�t�H�O�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

		//		�A���t�@�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	}
}

void FloorObject::Update()
{
}

void FloorObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto common = LibrarySingleton::GetInstance()->GetCommonState();

	//		�t���O��false�̏ꍇ���������Ȃ�	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	m_floorModel->Draw(context,
		*common,
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//		�|�X�g�G�t�F�N�g��
			if (flag & PostEffectFlag::Flag::Alpha)
			{
				// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}

			//		�|�X�g�G�t�F�N�g��
			if (flag & PostEffectFlag::Flag::Bloom)
			{
				// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
				context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
			}
		});

	//		���b�V���̕`��
	//drawMesh->StaticRender(m_objectMesh.get());
}

void FloorObject::Finalize()
{
	m_floorModel.reset();
	m_objectMesh->Finalize();
}

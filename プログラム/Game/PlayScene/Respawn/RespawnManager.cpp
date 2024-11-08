/*
* @file		RespawnManager.cpp
* @brief	リスポーンマネージャーの処理
* @author	Morita
* @date		2024/10/03
*/

#include "pch.h"

#include "RespawnManager.h"

RespawnManager::RespawnManager(GameManager* gameManager)
	:
	m_gameManager(gameManager),
	m_respownIndex(0),
	m_direction(0.0f)
{
	//		リスポーン座標読み込みを生成する
	m_respawnPointRead = std::make_unique<RespawnPointRead>();

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	m_respownRengeModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WireRange.cmo", *m_effect);
}

RespawnManager::~RespawnManager()
{
}

void RespawnManager::Initialize()
{
	//		初期スポーン位置
	m_respawnPosition = { 0.0f, 0.0f, 0.0f };

	m_respownIndex = 0;

	//		読み込み処理
	m_respawnPointRead->ReadProcess(0);
}

void RespawnManager::Update(DirectX::SimpleMath::Vector3 playerPosition)
{
	for (int i = 0, max = static_cast<int>(m_respawnPointRead->GetPosition().size());
		i < max; ++i)
	{
		//		要素数が同じ場合処理をしない
		if (i == m_respownIndex) continue;

		//		リスポーンポイントに当たっているか
		CollitionProcess(playerPosition, i);
	}
}

void RespawnManager::CollitionProcess(DirectX::SimpleMath::Vector3 playerPosition, int index)
{
	//		プレイヤーとリスポーンポイントの距離
	float length = (playerPosition - m_respawnPointRead->GetPosition()[index]).Length();

	//		距離がリスポーン範囲とプレイヤーの高さより小さい場合、更新する
	if (length < m_respawnPointRead->GetLength()[index] + 7.0f)
	{
		//		リスポーンポイントを更新する
		m_respawnPosition = m_respawnPointRead->GetPosition()[index];

		//		リスポーンインデックスを更新する
		m_respownIndex = index;

		//		方向
		m_direction = m_respawnPointRead->GetDirection()[index];
	}
}

void RespawnManager::DebugRender()
{
	//		デバック表示かどうか
	if (LibrarySingleton::GetInstance()->GetDebugJudgement())
	{
		for (int i = 0, max = static_cast<int>(m_respawnPointRead->GetPosition().size());
			i < max; ++i)
		{
			//		デバックワールドの半径の大きさ
			m_respownRengeWorld = DirectX::SimpleMath::Matrix::CreateScale(m_respawnPointRead->GetLength()[i] + 7.0f);

			//		座標を設定する
			m_respownRengeWorld *= DirectX::SimpleMath::Matrix::CreateTranslation(m_respawnPointRead->GetPosition()[i]);

			//		ワイヤーが届く範囲(半透明処理)
			for (const auto& it : m_respownRengeModel->meshes)
			{
				auto mesh = it.get();

				mesh->PrepareForRendering(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
					*LibrarySingleton::GetInstance()->GetCommonState(), true);

				mesh->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
					m_respownRengeWorld, LibrarySingleton::GetInstance()->GetView(),
					LibrarySingleton::GetInstance()->GetProj());
			}
		}
	}
}

void RespawnManager::Finalize()
{
	m_respawnPointRead->Finalize();

	m_direction = 0.0f;

	m_respownIndex = 0;
}


/*
* @file		TitleCommonProcess.h
* @brief	タイトル共通処理
* @author	Morita
* @date		2024/08/05
*/

#pragma once

#include "TitleInformation.h"

class TitleCommonProcess
{
public:

	//		コンストラクタ
	TitleCommonProcess(TitleInformation* m_information);

	//		デストラクタ
	~TitleCommonProcess();

	/*
	*	移動処理
	* 
	*	@param	(moveDirection)	移動する場所
	*	@param	(direction)		移動する向き
	*	@param	(time)			時間
	*	@param	(type)			移動するタイプ
	*/
	void MoveProcess(TitleInformation::MoveDirection moveDirection,
		bool direction, float time, TitleInformation::TitleUIType type);

private:

	/*
	*	中心から上への処理
	*
	*	@bool (direction)	true : 上へ移動する false : 中心へ移動する
	*/
	void CentreUP(bool direction, float time, TitleInformation::TitleUIType type);

	/*
	*	中心から下への処理
	*
	*	@bool (direction)	true : 下へ移動する false : 中心へ移動する
	*/
	void CenterUnder(bool direction, float time, TitleInformation::TitleUIType type);

	/*
	*	中心から下への処理
	*
	*	@bool (direction)	true : 下へ移動する false : 中心へ移動する
	*/
	void UPUnder(bool direction, float time, TitleInformation::TitleUIType type);

	/*
	*	シェーダーの描画
	* 
	*	@param	(type)	描画する種類
	*/
	inline void DrawShader(TitleInformation::TitleUIType type);

	/*
	*	減少処理
	*	
	*	@param	(time)	時間
	*/
	inline void DecreaseValue(float time);

	/*
	*	上昇処理
	*
	*	@param	(time)	時間
	*/
	inline void ElevatedValue(float time);

private:

	//		情報
	TitleInformation* m_information;

	//		遷移量(移動)
	float m_move;

	//		遷移量(サイズ)
	float m_size;

	//		初期座標
	DirectX::SimpleMath::Vector2 m_firstPosition;

	//		最終座標
	DirectX::SimpleMath::Vector2 m_endPosition;

	//		初期サイズ
	float m_firstSize;

	//		最終サイズ
	float m_endSize;

};

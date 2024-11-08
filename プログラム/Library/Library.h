/*
* @file		Library.h
* @brief	ライブラリ
* @author	Morita
* @date		2024/01/01
*/

#pragma once

#include <string>

#include <codecvt>

namespace Library
{
	/*
	*	クランプ処理
	*
	*	@param	(val)	値
	*	@param	(min)	最小値
	*	@param	(max)	最大値
	*	@return 値
	*/
	template<typename UIType>
	inline UIType Clamp(UIType val, UIType min, UIType max)
	{
		if (val >= max) return max;
		else if (val <= min) return min;

		return val;
	}

	/*
	*	ラープ処理
	*
	*	@param	(val1)	値１
	*	@param	(val2)	値２
	*	@param	(time)	時間
	*	@return 値
	*/
	inline float Lerp(const float& val1, const float& val2, const float& time)
	{
		return val1 + time * (val2 - val1);
	}

	inline DirectX::SimpleMath::Vector2 Lerp23(DirectX::SimpleMath::Vector2 position1,
		DirectX::SimpleMath::Vector2 position2,
		DirectX::SimpleMath::Vector2 position3,
		float time)
	{
		if (time < 0.5f)
		{
			return DirectX::SimpleMath::Vector2::
				Lerp(position1, position2, time * 2.0f);
		}
		else
		{
			return DirectX::SimpleMath::Vector2::
				Lerp(position2, position3, (time - 0.5f) * 2.0f);
		}
	}

	/*
	*	最大値を求める
	*
	*	@param	(val1)	値１
	*	@param	(val2)	値２
	*	@param	(val3)	値３
	*	@return		最大値
	*/
	inline DirectX::SimpleMath::Vector3 Max(const DirectX::SimpleMath::Vector3& val1,
		const DirectX::SimpleMath::Vector3& val2,
		const DirectX::SimpleMath::Vector3& val3)
	{
		return DirectX::SimpleMath::Vector3
		(std::max(val1.x, std::max(val2.x, val3.x)),
			std::max(val1.y, std::max(val2.y, val3.y)),
			std::max(val1.z, std::max(val2.z, val3.z))
		);
	}

	/*
	*	最小値を求める
	*
	*	@param	(val1)	値１
	*	@param	(val2)	値２
	*	@param	(val3)	値３
	*	@return		最小値
	*/
	inline DirectX::SimpleMath::Vector3 Min(const DirectX::SimpleMath::Vector3& val1,
		const DirectX::SimpleMath::Vector3& val2,
		const DirectX::SimpleMath::Vector3& val3)
	{
		return DirectX::SimpleMath::Vector3
		(std::min(val1.x, std::min(val2.x, val3.x)),
			std::min(val1.y, std::min(val2.y, val3.y)),
			std::min(val1.z, std::min(val2.z, val3.z))
		);
	}

	/*
	*	Stringをwstringに変換(AI参考)
	* 
	*	@param	(str)	文字列
	*	@return wstring
	*/
	inline std::wstring StringToWString(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		std::wostringstream oss;
		oss << converter.from_bytes(str);

		return converter.from_bytes(str);
	}
}

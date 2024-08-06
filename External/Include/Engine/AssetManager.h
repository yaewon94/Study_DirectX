#pragma once
#include "Asset.h"

// 에셋 관리 클래스
class AssetManager final : public Singleton<AssetManager>
{
	SINGLETON(AssetManager);

private:
	array<map<wstring, Asset*>, (UINT)ASSET_TYPE::COUNT_END> assetMapArr;

public:
	template<typename T> requires std::derived_from<T, Asset> Ptr<T> AddAsset(const wstring& Key, const wstring& relativePath);
	template<typename T> requires std::derived_from<T, Asset> Ptr<T> FindAsset(const wstring& Key, const wstring& relativePath=L"");
};

template<typename T> requires std::derived_from<T, Asset>
inline Ptr<T> AssetManager::AddAsset(const wstring& Key, const wstring& relativePath)
{
	auto& assetMap = assetMapArr[(UINT)T::Type];
	auto iter = assetMap.find(Key);

	if (iter == assetMap.end())
	{
		assetMapArr[(UINT)T::Type].insert(make_pair(Key, new T(Key, relativePath)));
		return FindAsset<T>(Key);
	}
	else
	{
		MessageBoxA(nullptr, "해당 KEY를 가진 에셋이 이미 존재합니다", "에셋 추가 실패", MB_OK);
		return Ptr<T>();
	}
}

template<typename T> requires std::derived_from<T, Asset>
inline Ptr<T> AssetManager::FindAsset(const wstring& Key, const wstring& relativePath)
{
	auto& assetMap = assetMapArr[(UINT)T::Type];
	auto iter = assetMap.find(Key);

	if (iter != assetMap.end()) return Ptr((T*)iter->second);
	else if (relativePath != L"") return AddAsset<T>(Key, relativePath);
	else return Ptr<T>();
}
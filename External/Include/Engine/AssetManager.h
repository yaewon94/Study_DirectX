#pragma once
#include "Asset.h"

class Texture;

// 에셋 관리 클래스
class AssetManager final : public Singleton<AssetManager>
{
	SINGLETON(AssetManager);

private:
	array<map<string, Ptr<Asset>>, (UINT)ASSET_TYPE::COUNT_END> assetMapArr;

public:
	int Init();

public:
	Ptr<Texture> CreateTexture(const string& Key, ComPtr<ID3D11Texture2D> texture);
	Ptr<Texture> CreateTexture(const string& Key, Vec2 size, DXGI_FORMAT format, UINT bindFlags, D3D11_USAGE usage = D3D11_USAGE_DEFAULT);

public:
	// 에셋 추가
	template<typename T> requires std::derived_from<T, Asset> 
	Ptr<T> AddAsset(const string& Key, const string& relativePath)
	{
		Ptr<T> asset = FindAsset<T>(Key);

		if (asset != nullptr)
		{
			MessageBox(nullptr, L"해당 KEY를 가진 에셋이 이미 존재합니다", L"에셋 추가 실패", MB_OK);
			return asset;
		}
		else
		{
			return AddAssetNoCheck<T>(Key, relativePath);
		}
	}

	// 에셋 찾기 (없으면 자동으로 메모리에 로드)
	template<typename T> requires std::derived_from<T, Asset> 
	Ptr<T> FindAsset(const string& Key, const string& relativePath = "")
	{
		auto& assetMap = assetMapArr[(UINT)GetType<T>()];
		const auto iter = assetMap.find(Key);

		if (iter != assetMap.end()) return (iter->second).ptr_dynamic_cast<T>();
		else if (relativePath != "") return AddAssetNoCheck<T>(Key, relativePath);
		else return nullptr;
	}

	void GetAssetNames(ASSET_TYPE type, vector<const char*>& vec);
	const map<string, Ptr<Asset>>& GetAssets(ASSET_TYPE type)
	{
		return assetMapArr[(UINT)type];
	}

private:
	// 에셋 추가
	template<typename T> requires std::derived_from<T, Asset>
	Ptr<T> AddAsset(const string& Key, Ptr<T>& asset)
	{
		assetMapArr[(UINT)GetType<T>()].insert(make_pair(Key, asset.ptr_dynamic_cast<Asset>()));

		return asset;
	}

	template<typename T> requires std::derived_from<T, Asset>
	Ptr<T> AddAssetNoCheck(const string& Key, const string& relativePath)
	{
		Ptr<T> asset = Ptr<T>(Key, relativePath);

		if (FAILED(asset->Load()))
		{
			MessageBox(nullptr, L"에셋 로드 실패", L"에셋 추가 실패", MB_OK);
			return nullptr;
		}

		assetMapArr[(UINT)GetType<T>()].insert(make_pair(Key, asset.ptr_dynamic_cast<Asset>()));

		return asset;
	}

private:
	int CreateDefaultMesh();
	int CreateDefaultShader();
	int CreateDefaultMaterial();
};
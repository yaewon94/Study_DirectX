#pragma once

class Animator2D;
class Camera;
class Collider;
class Collider2D;
class Component;
class Light;
class Light2D;
class MeshRender;
class RenderComponent;
class Script;
class TileMap;
class Transform;

// 컴포넌트 타입
enum class COMPONENT_TYPE
{
	// 사용자 정의 컴포넌트 타입
	SCRIPT = -100,

	// 조명 컴포넌트
	LIGHT = -3,
	// 콜라이더 컴포넌트
	COLLIDER = -2,
	// 렌더링 컴포넌트
	RENDER = -1,

	// 게임엔진 기본 컴포넌트
	CAMERA,
	TRANSFORM,
	COLLIDER_2D,
	LIGHT_2D, LIGHT_3D,
	MESH_RENDER, ANIMATOR_2D, TILEMAP
};

template<typename T> requires std::derived_from<T, Component>
static constexpr COMPONENT_TYPE GetType()
{
	//// TODO : 런타임에 컴포넌트 추가할때 오류 안나는지 확인
	if constexpr (std::is_base_of_v<Script, T>) return COMPONENT_TYPE::SCRIPT;
	if constexpr (std::is_same_v<T, Camera>) return COMPONENT_TYPE::CAMERA;

	if constexpr (std::is_same_v<T, Collider2D>) return COMPONENT_TYPE::COLLIDER_2D;
	if constexpr (std::is_same_v<T, Collider>) return COMPONENT_TYPE::COLLIDER;

	if constexpr (std::is_same_v<T, Light>) return COMPONENT_TYPE::LIGHT;
	if constexpr (std::is_same_v<T, Light2D>) return COMPONENT_TYPE::LIGHT_2D;

	if constexpr (std::is_same_v<T, Animator2D>) return COMPONENT_TYPE::ANIMATOR_2D;
	if constexpr (std::is_same_v<T, TileMap>) return COMPONENT_TYPE::TILEMAP;
	if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;
	if constexpr (std::is_same_v<T, RenderComponent>) return COMPONENT_TYPE::RENDER;

	if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;

	throw std::logic_error(MSG_INVALID_TYPE_CASTING);
}

template<typename T> requires std::derived_from<T, Component>
static constexpr bool IsRenderComponent()
{
	if constexpr (std::is_base_of_v<RenderComponent, T>) return true;
	else return false;
}

template<typename T> requires std::derived_from<T, Component>
static constexpr bool IsColliderComponent()
{
	if constexpr (std::is_base_of_v<Collider, T>) return true;
	else return false;
}

template<typename T> requires std::derived_from<T, Component>
static constexpr bool IsLightComponent()
{
	if constexpr (std::is_base_of_v<Light, T>) return true;
	else return false;
}
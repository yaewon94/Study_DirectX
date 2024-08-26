#pragma once

class Component;
class Transform;
class MeshRender;
class Script;

// 컴포넌트 타입
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
	, SCRIPT
};

template<typename T> requires std::derived_from<T, Component>
static COMPONENT_TYPE GetType()
{
	//// TODO : 런타임에 컴포넌트 추가할때 오류 안나는지 확인
	if constexpr (std::is_base_of_v<Script, T>) return COMPONENT_TYPE::SCRIPT;
	if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;
	if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;

	throw std::logic_error(MSG_INVALID_TYPE_CASTING);
}
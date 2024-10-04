#pragma once
#include "Component.h"
#include "CameraEnums.h"
#include "LayerEnums.h"
#include "Render.h"

class RenderComponent;

// 카메라 컴포넌트
// TODO : 메인 카메라, 일반 카메라 구별 (클래스 말고 다른 방법으로)
class Camera final : public Component
{
private:
	PROJECTION_TYPE m_projType;	// 투영 타입
	float m_near, m_far;		// 렌더링 범위에 해당되는 z축 최소값, 최대값
	float m_aspectRatio;		// 투영 범위 종횡비
	LAYER_TYPES m_layers;		// 렌더링할 레이어 조합

	// 원근투영 (PROJECTION_TYPE::PERSPECTIVE)
	float m_fov;	// field of view (시야각)

	// 직교투영 (PROJECTION_TYPE::ORTHOGRAPHIC)
	float m_width;	// 투영 가로길이
	float m_scale;	// 투영 배율

	// 변환행렬
	Matrix m_matView;	// view 행렬
	Matrix m_matProj;	// projection 행렬

	// 렌더링 순서
	// (한번 설정된 SHADER_DOMAIN, LAYER_TYPE이 바뀌는 경우는 거의 없으므로 list말고 vector사용)
	map<SHADER_DOMAIN, map<LAYER_TYPE, vector<Ptr<RenderComponent>>>> m_renderMap;

public:
	Camera(const Ptr<GameObject>& owner);
	Camera(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Camera();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Camera>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	void SetLayerOnOff(LAYER_TYPE layer);
	void AddRenderObj(const Ptr<GameObject>& obj);
	void DeleteRenderObj(const Ptr<GameObject>& obj);

public:
	virtual void Init() final;
	virtual void FinalTick() final;
	void Render();

private:
	void OnChangeRotation();
};
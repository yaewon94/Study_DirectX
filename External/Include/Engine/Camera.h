#pragma once
#include "Component.h"
#include "CameraValues.h"
#include "LayerValues.h"
#include "Render.h"

class RenderComponent;

// 카메라 컴포넌트
// TODO : 메인 카메라, 일반 카메라 구별 (클래스 말고 다른 방법으로)
class Camera final : public Component
{
private:
	CAMERA_TYPE m_type;					// 카메라 타입 (렌더링 우선순위)
	PROJECTION_TYPE m_projType;			// 투영 타입
	float m_near, m_far;				// 렌더링 범위에 해당되는 z축 최소값, 최대값
	float m_viewWidth, m_viewHeight;	// 렌더링할 가로, 세로 크기
	LAYER_TYPES m_layers;				// 렌더링할 레이어 조합

	// 원근투영 (PROJECTION_TYPE::PERSPECTIVE)
	float m_fov;	// field of view (시야각)

	// 직교투영 (PROJECTION_TYPE::ORTHOGRAPHIC)
	float m_scale;	// 투영 배율

	// 렌더링 순서
	// (한번 설정된 SHADER_DOMAIN, LAYER_TYPE이 바뀌는 경우는 거의 없으므로 list말고 vector사용)
	array<map<LAYER_TYPE, vector<Ptr<RenderComponent>>>, (UINT)SHADER_DOMAIN::COUNT_END> m_renderObjs;

public:
	Camera(const Ptr<GameObject>& owner);
	Camera(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Camera();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Camera>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	CAMERA_TYPE GetCameraType() { return m_type; }
	void SetCameraType(CAMERA_TYPE type);

	PROJECTION_TYPE GetProjectionType() { return m_projType; }
	void SetProjectionType(PROJECTION_TYPE type) { m_projType = type; OnChangeProjectionType(); }

	float GetNear() { return m_near; }
	void SetNear(float Near);
	float GetFar() { return m_far; }
	void SetFar(float Far);

	float GetViewWidth() { return m_viewWidth; }
	void SetViewWidth(float width);
	float GetViewHeight() { return m_viewHeight; }
	void SetViewHeight(float height);

	// perspective
	float GetFieldOfView() { return m_fov; }
	void SetFieldOfView(int fov);	// @fov : 0 ~ 360

	// orthographic
	float GetScale() { return m_scale; }
	void SetScale(float scale);

	void SetLayerOnOff(LAYER_TYPE layer);
	LAYER_TYPES GetRenderLayers() { return m_layers; }

	void AddRenderObj(const Ptr<GameObject>& obj);
	void DeleteRenderObj(const Ptr<GameObject>& obj);

public:
	virtual void Init() final;
	virtual void FinalTick() final;
	void Render();

private:
	void OnChangeProjectionType();
	void OnChangeProjectionMatrix();
	void OnChangeRotation();
};
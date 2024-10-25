#pragma once
#include "Component.h"
#include "CameraValues.h"
#include "LayerValues.h"
#include "Render.h"

class RenderComponent;

// ī�޶� ������Ʈ
// TODO : ���� ī�޶�, �Ϲ� ī�޶� ���� (Ŭ���� ���� �ٸ� �������)
class Camera final : public Component
{
private:
	CAMERA_TYPE m_type;					// ī�޶� Ÿ�� (������ �켱����)
	PROJECTION_TYPE m_projType;			// ���� Ÿ��
	float m_near, m_far;				// ������ ������ �ش�Ǵ� z�� �ּҰ�, �ִ밪
	float m_viewWidth, m_viewHeight;	// �������� ����, ���� ũ��
	LAYER_TYPES m_layers;				// �������� ���̾� ����

	// �������� (PROJECTION_TYPE::PERSPECTIVE)
	float m_fov;	// field of view (�þ߰�)

	// �������� (PROJECTION_TYPE::ORTHOGRAPHIC)
	float m_scale;	// ���� ����

	// ������ ����
	// (�ѹ� ������ SHADER_DOMAIN, LAYER_TYPE�� �ٲ�� ���� ���� �����Ƿ� list���� vector���)
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
	virtual COMPONENT_TYPE GetBaseType() final { return COMPONENT_TYPE::CAMERA; }

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

	float GetFieldOfView() { return m_fov; }
	// mode : perspective, @fov : 0 ~ 360
	void SetFieldOfView(int fov);

	float GetScale() { return m_scale; }
	// mode : orthographic
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
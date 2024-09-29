#pragma once
#include "MeshRender.h"

class Sprite;

// 애니메이션 재생 컴포넌트
class Animator2D final : public MeshRender
{
	NO_COPY_ASSIGN(Animator2D);

private:
	map<string, Ptr<Sprite>> m_spriteMap;
	Ptr<Sprite> m_curAnim;
	UINT m_curIndex;
	float m_playTime;

public:
	Animator2D(const Ptr<GameObject>& owner);
	Animator2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Animator2D();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Animator2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	void AddSprite(const string& Key, const Ptr<Sprite>& sprite);
	void ChangeAnimation(const string& Key);

public:
	virtual void FinalTick() final;
	virtual void Render() final;
};
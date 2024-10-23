#pragma once

// 오브젝트, 컴포넌트, 에셋 등의 최상위 클래스
// TODO : 추상클래스로 만들기
class Entity : public IPtrReleasable
{
private:
	static UINT nextID;

private:
	const UINT ID;

public:
	UINT GetID() { return ID; }

protected:
	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();
};
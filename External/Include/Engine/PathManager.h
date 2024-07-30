#pragma once

// 경로 처리 클래스
class PathManager final : public Singleton<PathManager>
{
	SINGLETON(PathManager);

private:
	wstring contentPath;

public:
	wstring GetContentPath() { return contentPath; }

public:
	void Init();
};
#ifndef _SCENE_MGR_H_
#define _SCENE_MGR_H_

#include <unordered_map>
#include "Scene.h"
#include "IScenePtr.h"

class SceneMgr {
public:
	SceneMgr();
	void init();
	void update();
	void draw() const;
	void end();
	void add(Scene name, const IScenePtr& scene);
	void change(Scene name);

	SceneMgr(const SceneMgr& other) = delete;
	SceneMgr operator = (const SceneMgr& other) = delete;

private:
	std::unordered_map<Scene, IScenePtr>scenes_;
	IScenePtr currentScene_;
};

#endif
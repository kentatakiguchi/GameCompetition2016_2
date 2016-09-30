#include "SceneMgr.h"
#include "SceneNull.h"

SceneMgr::SceneMgr() :
	currentScene_(std::make_shared<SceneNull>()) {
}

void SceneMgr::init() {
	scenes_.clear();
}

void SceneMgr::update() {
	currentScene_->update();
	if (currentScene_->isEnd())
	{
		change(currentScene_->next());
	}
}

void SceneMgr::draw() const {
	currentScene_->draw();
}

void SceneMgr::end() {
	currentScene_->end();
	currentScene_ = std::make_shared<SceneNull>();
}

void SceneMgr::add(Scene name, const IScenePtr& scene) {
	scenes_[name] = scene;
}

void SceneMgr::change(Scene name) {
	currentScene_->isEnd_ = false;
	end();
	currentScene_ = scenes_[name];
	currentScene_->start();
}

#pragma once

#include "F7/Graphic/Camera/Camera.hpp"
#include "F7/Graphic/Model.hpp"
#include <vector>
#include <mutex>

class Scene
{  
public:
	Scene() { init(); }
	~Scene() {}

	void init();
	void display();
	void addModel(Model* pModel) { _models.push_back(pModel); }
	void useRenderingProgram(GLuint id);
	void endRenderingProgram();

	void setCamera(Camera* camera) { _camera = camera; }

	//Camera& camera() { return _camera; }

	std::mutex _sceneMutex;
private:
	Camera* _camera;
	std::vector<Model*> _models;
	GLuint _curRenderingProgramID{ 0 };
	Model* _needAddModel;
	
	
	float deltaTime{ 0 };	// time between current frame and last frame
	float lastFrame{ 0 };
	bool firstMouse{ true };

	GLuint _projViewWorldMatLoc;	// ???վ?????ַ
	GLuint _worldMatLoc;	// ??????????ַ
	GLuint _viewMatLoc;	// ?ӽǾ?????ַ
	GLuint _projMatLoc;	// ͶӰ??????ַ
	F7::Mat4 _projViewWorldMat;	// ???վ???
	F7::Mat4 _projMat;			// ͶӰ????
	F7::Mat4 _viewMat;			// ?ӽǾ???
	F7::Mat4 _worldMat;			// ????????
};


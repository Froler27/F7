#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "F7/F7.hpp"
#include "F7/Graphic/Shader/ShaderProgram.hpp"
#include "F7/Graphic/Material.hpp"
#include "F7/Graphic/LightSource.hpp"
#include "F7/Graphic/Camera/Camera.hpp"


class BoundBox
{
public:
	using value_type = float;
	BoundBox() {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);
	}

	void draw();

	void setLWH(F7::Vec3 lwh) { _lwh = lwh; }

	void init();

	F7::Vec3 _lwh{ 0 };

	std::vector<F7::Vec3> _verts;
	std::vector<int> _indices;

	GLuint _vao{ 0 };
	GLuint _vbo{ 0 };
	GLuint _ebo{ 0 };
	std::shared_ptr<ShaderProgram> _spShader;
	static GLuint _shaderProgID;
};

class Model
{
public:
	enum class EDataType
	{
		Vertex = 1,
		Color = 2,
		Normal = 4,
		TexCoord = 8
	};
	enum class EBindingType
	{
		Off = 0,
		Overall,
		Per_Vertex
	};
	using value_type = float;
public:
	Model() {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		//glGenBuffers(1, &_ebo);
	}
	~Model() {}

	bool loadModelFile(const char* modelPath);
	bool loadModelFile(const std::string& modelPath) { return loadModelFile(modelPath.c_str()); }
	bool loadTexture(const char* texturePath, const char* uniformName, int texUnit);
	bool loadTexture(const std::string& texturePath, const std::string& uniformName, int texUnit) { return loadTexture(texturePath.c_str(), uniformName.c_str(), texUnit); }
	virtual void genData() {}
	void configData_v();
	void configData_v_n();
	void configData_v_n_tc();

	void useTexture();
	inline void genEBO();
	bool validEBO() { return _bUseEBO; }
	virtual void draw();

	void setColorBinding(EBindingType eType) { _colorBinding = eType; }
	void setNormalBinding(EBindingType eType) { _normalBinding = eType; }

	void setShaderProgram(ShaderProgram* pShader) { _spShader = std::shared_ptr<ShaderProgram>(pShader); }
	void setShaderProgram(std::shared_ptr<ShaderProgram>& spShader) { _spShader = spShader; }
	virtual void setBoundShaderProgram(std::shared_ptr<ShaderProgram>& ) { }
	std::shared_ptr<ShaderProgram>& getShaderProgram() { return _spShader; }

	F7::Mat4 getWorldMatrix();
	GLuint getVAO() { return _vao; }
	size_t getVertsNum() { return _verts.size(); }

	std::vector<value_type>& getData() { return _verts; }
	const std::vector<value_type>& getData() const { return _verts; }

	F7::Vec3& position() { return _pos; }
	F7::Vec3& rotate() { return _rot; }
	F7::Vec3& scale() { return _sca; }

	void push_back_vec2(F7::Vec2_T<value_type> v) {
		_verts.push_back(v[0]);
		_verts.push_back(v[1]);
	}
	void push_back_vec3(F7::Vec3_T<value_type> v) {
		_verts.push_back(v[0]);
		_verts.push_back(v[1]);
		_verts.push_back(v[2]);
	}

	void setMaterial(const Material& pMaterial);
	void setGlobalAmbient(const Vec4f& globalAmbient);
	void setLight(const PointLight& pLightSource);

	void initBoundRadiusByLWH() {
		_boundRadius = _boundLWH.length() / 2;
	}

	void setCamera(Camera* pCamera) { _camera = pCamera; }
	void showBoundBox(bool bShow = true) { _showBoundBox = bShow; }
	bool isShowed() { return _showBoundBox; }
	F7::Vec3 getBoundBoxLWH() const { return _boundLWH; }
	value_type getBoundRadius() const { return _boundRadius; }

protected:
	GLuint _vao{ 0 };
	GLuint _vbo{ 0 };
	GLuint _ebo{ 0 };
	std::shared_ptr<ShaderProgram> _spShader;

	bool _bUseEBO{ false };
	std::map<int, GLuint> _textureMap;

	EBindingType _colorBinding{ EBindingType::Off };
	EBindingType _normalBinding{ EBindingType::Off };

	F7::Vec3 _pos{ 0 };
	F7::Vec3 _rot{ 0 };
	F7::Vec3 _sca{ 1 };
	Material* _pMaterial{ nullptr };

	std::vector<value_type> _verts;
	std::vector<int> _indices;
	int _vertsNum{ 0 };
	int _vertSize{ 0 };

	F7::Vec3 _boundLWH{ 1 };
	value_type _boundRadius{ 1 };

	bool _showBoundBox{ false };
	Camera* _camera{ nullptr };
};

class Cube : public Model
{
public:
	using value_type = float;
	Cube() {}
	Cube(value_type sideLength) : _sideLength(sideLength) { 
		_boundLWH = sideLength;
		initBoundRadiusByLWH();
	}

	value_type& length() { return _sideLength; }
	const value_type length() const { return _sideLength; }

	virtual void genData() override;
	virtual void draw() override;

private:
	value_type _sideLength{ 1 };
};

class Segment : public Model
{
public:
	using value_type = float;
	Segment() {}
	Segment(Vec3_T<value_type> point1, Vec3_T<value_type> point2) {
		push_back_vec3(point1);
		push_back_vec3(point2);
	}
	virtual void genData() override;
	virtual void draw() override;
};

class Sphere: public Model
{
public:
	using value_type = float;
	Sphere() { init(); }
	Sphere(value_type radius, int prec) : _radius(radius), _prec(prec) { init(); }

	virtual void genData() override;
	virtual void draw() override;

	void setRaius(value_type radius) { _radius = radius; }
	void setPrec(int prec) { _prec = prec; }
	

private:
	void init();

	value_type _radius{ 1 };// �뾶
	int _prec{30}; // ���ȣ�������ŷ�Ϊ_prec�ݣ����ŷ�Ϊ_prec*2�ݣ����վ�γ�ȵķ�ʽ
};

class Torus : public Model
{
public:
	using value_type = float;
	Torus() { init(); }

	virtual void genData() override;
	virtual void draw() override;

	void setRadius(value_type r1, value_type r2) { _radius1 = r1; _radius2 = r2; }
	void setPrec(int prec1, int prec2) { _prec1 = prec1; _prec2 = prec2; }
	virtual void setBoundShaderProgram(std::shared_ptr<ShaderProgram>& spProg) { _boundBox._spShader = spProg; }
	
private:
	void init();
	value_type _radius1{ 1 };
	value_type _radius2{ 0.5 };
	int _prec1{ 60 };
	int _prec2{ 30 };
	BoundBox _boundBox;
};

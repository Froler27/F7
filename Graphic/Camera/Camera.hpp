#pragma once

#include "F7/Vec/Vec.h"
#include "F7/Matrix/Mat.h"
#include "F7/Common/Log.hpp"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(F7::Vec3 pos = F7::Vec3(), F7::Vec3 up = F7::Vec3(0.f, 0.f, 1.f), float yaw = YAW, float pitch = PITCH);
		
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		
	F7::Vec2 getNDCCoord(const F7::Vec2& sceenCoord) const {
		F7::Vec2 res;
		res.x() = (sceenCoord.x() / _width * 2 - 1);
		res.y() = (1 - sceenCoord.y() / _height * 2);
		return res;
	}
	F7::Vec3 getNDCCoord(const F7::Vec3& sceenCoord) const {
		F7::Vec3 res;
		res.x() = (sceenCoord.x() / _width*2 - 1);
		res.y() = (1 - sceenCoord.y() / _height*2);
		res.z() = F7::Math::clamp(sceenCoord.z() * 2 - 1, F7::Vec3::value_type(-1), F7::Vec3::value_type(1));
		return res;
	}
	F7::Vec3 getViewCoordFromNDC(const F7::Vec3& NDCCoord) const {
		F7::Vec3 res;
		res = NDCCoord;
		res.z() = 2 * _far * _near / (NDCCoord.z() * (_far - _near) - (_far + _near));
		res.y() = NDCCoord.y() * F7::Math::tan(F7::Math::Degree2Radian(_zoom) * 0.5f) * (-res.z());
		res.x() = NDCCoord.x() * F7::Math::tan(F7::Math::Degree2Radian(_zoom) * 0.5f)*_aspect * (-res.z());
		return res;
	}
	F7::Vec3 getScreenCoordFromNDC(const F7::Vec3& NDCCoord) const {
		F7::Vec3 res;
		res.x() = (NDCCoord.x() + 1) * 0.5 * _width;
		res.y() = (1 - NDCCoord.y()) * 0.5 * _height;
		res.z() = (NDCCoord.z() + 1) * 0.5;
		return res;
	}
	void setPos(F7::Vec3 pos) { _pos = pos; }
	void setPos(float x, float y, float z) { _pos.x() = x; _pos.y() = y; _pos.z() = z; }
	void addMouseMoveSpeed(float x) { _moveSpeed += x; }

	inline F7::Mat4 getViewMatrix() { return F7::Mat4::LookAt(_pos, _pos + _front, _up); }
	inline F7::Mat4 getProjMatrix() { return F7::Mat4::Perspective(F7::Math::Degree2Radian(_zoom), _aspect, _near, _far); }
	inline F7::Mat4 getViewInverseMatrix() { F7::Mat4 res = getViewMatrix(); res.invert(); return res; }
	inline F7::Mat4 getProjInverseMatrix() { F7::Mat4 res = getProjMatrix(); res.invert(); return res; }

	void processKeyboard(Camera_Movement direction, float deltaTime);

	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yoffset)
	{
		_zoom -= (float)yoffset;
		if (_zoom < 1.0f)
			_zoom = 1.0f;
		if (_zoom > 160.0f)
			_zoom = 160.0f;
	}
private:
	void updateCameraVectors();

public:
	F7::Vec3 _pos;
	F7::Vec3 _front{ 0,1,0 };
	F7::Vec3 _up;
	F7::Vec3 _right;
	F7::Vec3 _wordUp;
	int _width;
	int _height;
	float _near{ 1 };
	float _far{100};

	float _aspect{ 1 };

	float _yaw;
	float _pitch;

	float _moveSpeed;
	float _mouseSensitivity;
	float _zoom;
};
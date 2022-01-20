#pragma once

#include "Vec.hpp"

namespace F7
{

	typedef Vec2_T<int>		Vec2i;
	typedef Vec2_T<float>	Vec2f;
	typedef Vec2_T<double>	Vec2d;

	typedef Vec3_T<int>		Vec3i;
	typedef Vec3_T<float>	Vec3f;
	typedef Vec3_T<double>	Vec3d;

	typedef Vec4_T<int>		Vec4i;
	typedef Vec4_T<float>	Vec4f;
	typedef Vec4_T<double>	Vec4d;

	typedef Color_T<float>	Colorf;
	typedef Color_T<double>	Colord;

	typedef Vec2f Vec2;
	typedef Vec3f Vec3;
	typedef Vec4f Vec4;
	typedef Colorf Color;
	class Color255;

// 	template class Vec2_T<int>;
// 	template class Vec2_T<float>;
// 	template class Vec2_T<double>;
// 
// 	template class Vec3_T<int>;
// 	template class Vec3_T<float>;
// 	template class Vec3_T<double>;
// 
// 	template class Vec4_T<int>;
// 	template class Vec4_T<float>;
// 	template class Vec4_T<double>;
// 
// 	template class Color_T<float>;
// 	template class Color_T<double>;
}
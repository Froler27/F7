#pragma once

#include "Face.hpp"

namespace F7
{

	template class Plane_T<float>; using Planef = Plane_T<float>;
	template class Plane_T<double>; using Planed = Plane_T<double>;

	template class Rectangle_T<float>; using Rectanglef = Rectangle_T<float>;
	template class Rectangle_T<double>; using Rectangled = Rectangle_T<double>;

}
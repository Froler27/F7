#pragma once

#include "Volume.hpp"

namespace F7
{

	template class Cuboid_T<float>	; using Cuboidf = Cuboid_T<float>;
	template class Cuboid_T<double>	; using Cuboidd = Cuboid_T<double>;

}
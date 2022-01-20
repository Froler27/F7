#pragma once

#include "Line.hpp"

namespace F7
{

	template class StraightLine_T<float>	; using StraightLinef = StraightLine_T<float>;
	template class StraightLine_T<double>	; using StraightLined = StraightLine_T<double>;

	template class Segment_T<float>; using Segmentf = Segment_T<float>;
	template class Segment_T<double>; using Segmentd = Segment_T<double>;

}
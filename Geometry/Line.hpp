#pragma once

#include <functional>
#include "F7/Vec/Vec.h"

namespace F7
{

	template <typename T>
	class Segment_T
	{
	public:
		using value_type = T;
		using vec3_type = Vec3_T<value_type>;
		Segment_T() :_endPoint(0, 0, 1) {}
		Segment_T(const vec3_type& startPoint, const vec3_type& endPoint)
			: _startPoint(startPoint), _endPoint(endPoint)
		{}

		value_type length2() const {
			return (_endPoint - _startPoint).length2();
		}
		value_type length() const {
			return (_endPoint - _startPoint).length();
		}
		vec3_type getDirection() const {
			return (_endPoint - _startPoint).normalize();
		}

		vec3_type getPoint(value_type t) const {
			return _startPoint * (1 - t) + _endPoint * t;
		}

		const vec3_type& getStartPoint() const { return _startPoint; }
		const vec3_type& getEndPoint() const { return _endPoint; }
		void setEndPoint(const vec3_type& point) { _endPoint = point; }
		void setStartPoint(const vec3_type& point) { _startPoint = point; }

	private:
		vec3_type _startPoint;
		vec3_type _endPoint;
	};

	template <typename T>
	class StraightLine_T
	{
	public:
		using value_type = T;
		using vec3_type = Vec3_T<value_type>;
		StraightLine_T() :_direct(0, 0, 1) {}
		StraightLine_T(const Segment_T<value_type>& segment) 
			: _point(segment.getStartPoint()), _direct(segment.getDirection()) 
		{}
		StraightLine_T(const vec3_type& startPoint, const vec3_type& endPoint)
			: _point(startPoint), _direct((endPoint - startPoint).normalize())
		{}

		const vec3_type& getDirection() const {
			return _direct;
		}
		vec3_type getPoint(value_type t = 0) const {
			return _point + _direct * t;
		}
	private:
		vec3_type _point;
		vec3_type _direct;
	};

// 	template <typename T>
// 	class Curve_T
// 	{
// 	public:
// 		Curve_T() {}
// 		virtual ~Curve_T() {}
// 
// 	protected:
// 		std::vector<vec3_type> _v;
// 	};

// 	template <typename T>
// 	class BezierCurve2_T: public Curve_T<T>
// 	{
// 	public:
// 		using value_type = T;
// 		using base_type = Curve_T<T>;
// 		using vec3_type = Vec3_T<value_type>;
// 		BezierCurve2_T() {}
// 
// 	private:
// 		
// 	};
// 
// 	template <typename T>
// 	class BezierCurve3_T : public Curve_T<T>
// 	{
// 	public:
// 		using value_type = T;
// 		using base_type = Curve_T<T>;
// 		using vec3_type = Vec3_T<value_type>;
// 		BezierCurve3_T() {}
// 
// 	private:
// 
// 	};


}


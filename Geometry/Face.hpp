#pragma once

#include <array>

#include "F7/Vec/Vec.hpp"
#include "Line.hpp"

namespace F7
{

	template <typename T>
	class Plane_T
	{
	public:
		using value_type = T;
		using vec3_type = Vec3_T<value_type>;
		virtual ~Plane_T(){}
		Plane_T(){}
		Plane_T(const vec3_type& point1, const vec3_type& point2, const vec3_type& point3) {
			_point = point1;
			vec3_type vec1 = point1 - point2;
			vec3_type vec2 = point3 - point2;
			vec3_type res = vec2 ^ vec1;
			res.normalize();
			A = res.x();
			B = res.y();
			C = res.z();
			D = -(res * _point);
		}
		// TODO: Plane(ABCD){}

		vec3_type getDirection() const {
			return vec3_type(A, B, C);
		}
		const vec3_type& getPoint() const {
			return _point;
		}

		void setABCD(value_type a, value_type b, value_type c, value_type d) {
			A = a;
			B = b;
			C = c;
			D = d;
		}
		bool valid() const {
			vec3_type tem(A, B, C);
			if (tem.isZero() || !tem.valid())
				return false;
			return true;
		}
		bool standardization() {
			if (!valid()) {
				return false;
			}
			value_type len = getDirection().length();
			if (len == 0)
				return false;
			A /= len;
			B /= len;
			C /= len;
			D /= len;
			vec3_type point;
			bool tag = getZ(point);
			if (!tag) {
				tag = getY(point);
				if (!tag) {
					tag = getX(point);
					if (!tag)
						return false;
				}
			}
			_point = point;
			return true;
		}

		bool pointInPlane(const vec3_type& point) {
			return point* getDirection() + D == 0;
		}

		value_type getDist(const vec3_type& point) const {
			vec3_type vec1 = point - _point;
			return vec3_type(A, B, C) * vec1;
		}

		bool getIntersectionPoint(const StraightLine_T<value_type>& line, vec3_type& intersectionPoint) const {
			// TODO: 精度问题
			value_type tem = line.getDirection() * getDirection();
			if (tem == 0) { // 直线与平面平行
				if (getDist(line.getPoint()) == 0) { // 直线在平面上
					intersectionPoint.makeInvalid();
				}
				else {
					return false;
				}
			}
			else {
				value_type t = -(getDirection() * line.getPoint() + D) / tem;
				intersectionPoint = line.getPoint(t);
			}
			return true;
		}

		bool getIntersectionPoint(const Segment_T<value_type>& segment, vec3_type& intersectionPoint) const {
			value_type dist1 = getDist(segment.getStartPoint());
			value_type dist2 = getDist(segment.getEndPoint());
			if ((dist1 > 0 && dist2 > 0) || (dist1 < 0 && dist2 < 0)) {
				return false;
			}
			if (dist1 != 0 && dist2 != 0) {
				StraightLine_T<value_type> straightLine(segment);
				return getIntersectionPoint(straightLine, intersectionPoint);// 一定为 true
			}
			else if (dist1 == 0 && dist2 == 0) {// 线段在平面上
				intersectionPoint.makeInvalid();
			}
			else if (dist1 == 0) {
				intersectionPoint = segment.getStartPoint();
			}
			else if (dist2 == 0) {
				intersectionPoint = segment.getEndPoint();
			}
			return true;
		}

		bool getX(value_type& x, value_type y, value_type z) const {
			value_type tem = B * y + C * z + D;
			if (A == 0) {
				if (tem != 0) {
					return false;
				}
			}
			else {
				z = -tem / A;
			}
			return true;
		}
		bool getX(vec3_type& point) const {
			return getX(point.x(), point.y(), point.z());
		}
		bool getY(value_type x, value_type& y, value_type z) const {
			value_type tem = A * x + C * z + D;
			if (B == 0) {
				if (tem != 0) {
					return false;
				}
			}
			else {
				z = -tem / B;
			}
			return true;
		}
		bool getY(vec3_type& point) const {
			return getY(point.x(), point.y(), point.z());
		}
		bool getZ(value_type x, value_type y, value_type& z) const {
			if (C == 0) {
				value_type tem = A * x + B * y + D;
				if (tem != 0) {
					return false;
				}
			}
			else {
				z = -(A * x + B * y + D) / C;
			}
			return true;
		}
		bool getZ(vec3_type& point) const {
			return getZ(point.x(), point.y(), point.z());
		}


	protected:
		vec3_type _point;// 0,0,0
		value_type A{0};
		value_type B{0};
		value_type C{1};
		value_type D{0};
	};

	template <typename T>
	class Rectangle_T : public Plane_T<T>
	{
	public:
		using value_type = T;
		using vec3_type = Vec3_T<T>;
		using base_type = Plane_T<T>;
		static const int N{ 4 };

		Rectangle_T() {}
		Rectangle_T(const vec3_type& point1, const vec3_type& point2, const vec3_type& point3, const vec3_type& point4)
			: base_type(point1, point2, point3)
		{
			_points[0] = point1;
			_points[1] = point2;
			_points[2] = point3;
			_points[3] = point4;
		}

		bool getIntersectionPoint(const Segment_T<value_type>& segment, vec3_type& intersectionPoint) const {
			bool tag = base_type::getIntersectionPoint(segment, intersectionPoint);
			if (tag) {// 得到了和平面的交点
				if (!intersectionPoint.valid()) {// 交点无效表明线段在平面上
					// TODO: 判断线段和矩形有无相交
					tag = false;
				}
				else {
					tag = pointInRect(intersectionPoint);//交点在矩形区域内
				}
			}
			return tag;
		}
		// 未判断点是否在矩形平面上
		bool pointInRect(const vec3_type& point) const {
			vec3_type AP = point - _points[0];
			vec3_type BP = point - _points[1];
			vec3_type CP = point - _points[2];
			vec3_type DP = point - _points[3];

			vec3_type AB = _points[1] - _points[0];
			vec3_type BC = _points[2] - _points[1];
			vec3_type CD = _points[3] - _points[2];
			vec3_type DA = _points[0] - _points[3];

			return (AB ^ AP) * (CD ^ CP) >= 0 && (DA ^ DP) * (BC ^ BP) >= 0;
		}

	protected:
		//vec3_type _points[N];
		std::array<vec3_type, N> _points;
	};
}


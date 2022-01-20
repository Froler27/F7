#pragma once

#include "F7/Vec/Vec.hpp"
#include "Face.hpp"
#include <array>

namespace F7
{
	// 前左下方点，前右下方1，后右下方2，后左下方3，前左上方4，前右上方5，后右上方6，后左上方7
	template <typename T>
	class Cuboid_T
	{
	public:
		using value_type = T;
		using vec3_type = Vec3_T<T>;
		using rect_type = Rectangle_T<T>;
		using edge_type = Segment_T<T>;
		using points_type = std::array<vec3_type, 8>;
		static const int N = 8;// number of points
		static const int NumFaces = 6;
		static const int NumEdges = 12;

		Cuboid_T() {}
		Cuboid_T(const points_type& points): _points(points)
		{}
		Cuboid_T(const vec3_type* pPoints) {
			for (int i = 0; i < N; i++) {
				_points[i] = *(pPoints + i);
			}
		}
		Cuboid_T(const value_type* pPoints) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < 3; j++) {
					_points[i][j] = pPoints[i * 3 + j];
				}
			}
		}
		Cuboid_T(const vec3_type& point1, const vec3_type& point2, const vec3_type& point3, const vec3_type& point4,
			const vec3_type& point5, const vec3_type& point6, const vec3_type& point7, const vec3_type& point8)
		{
			_points[0] = point1;
			_points[1] = point2;
			_points[2] = point3;
			_points[3] = point4;
			_points[4] = point5;
			_points[5] = point6;
			_points[6] = point7;
			_points[7] = point8;
		}

		void generatePoints(const vec3_type& vec3HalfLWH) {
			_points[0] = { -vec3HalfLWH.x(), -vec3HalfLWH.y(), -vec3HalfLWH.z()};
			_points[1] = {  vec3HalfLWH.x(), -vec3HalfLWH.y(), -vec3HalfLWH.z()};
			_points[2] = {  vec3HalfLWH.x(), -vec3HalfLWH.y(),  vec3HalfLWH.z()};
			_points[3] = { -vec3HalfLWH.x(), -vec3HalfLWH.y(),  vec3HalfLWH.z()};
			_points[4] = { -vec3HalfLWH.x(),  vec3HalfLWH.y(), -vec3HalfLWH.z() };
			_points[5] = {  vec3HalfLWH.x(),  vec3HalfLWH.y(), -vec3HalfLWH.z() };
			_points[6] = {  vec3HalfLWH.x(),  vec3HalfLWH.y(),  vec3HalfLWH.z() };
			_points[7] = { -vec3HalfLWH.x(),  vec3HalfLWH.y(),  vec3HalfLWH.z() };
		}

		edge_type getEdge(int id) const {
			int idStart = 0, idEnd = 0;
			switch (id)
			{
			case 0:
				idStart = 0;
				idEnd = 1;
				break;
			case 1:
				idStart = 1;
				idEnd = 2;
				break;
			case 2:
				idStart = 2;
				idEnd = 3;
				break;
			case 3:
				idStart = 3;
				idEnd = 0;
				break;
			case 4:
				idStart = 0;
				idEnd = 4;
				break;
			case 5:
				idStart = 1;
				idEnd = 5;
				break;
			case 6:
				idStart = 2;
				idEnd = 6;
				break;
			case 7:
				idStart = 3;
				idEnd = 7;
			case 8:
				idStart = 4;
				idEnd = 5;
				break;
			case 9:
				idStart = 5;
				idEnd = 6;
				break;
			case 10:
				idStart = 6;
				idEnd = 7;
				break;
			case 11:
				idStart = 7;
				idEnd = 0;
				break;
			default:
				break;
			}
			return edge_type(_points[idStart], _points[idEnd]);
		}

		rect_type getRect(int id) const {
			int ids[4]{};
			switch (id)
			{
			case 0:
				ids[0] = 0;
				ids[1] = 3;
				ids[2] = 2;
				ids[3] = 1;
				break;
			case 1:
				ids[0] = 0;
				ids[1] = 1;
				ids[2] = 5;
				ids[3] = 4;
				break;
			case 2:
				ids[0] = 1;
				ids[1] = 2;
				ids[2] = 6;
				ids[3] = 5;
				break;
			case 3:
				ids[0] = 2;
				ids[1] = 3;
				ids[2] = 7;
				ids[3] = 6;
				break;
			case 4:
				ids[0] = 3;
				ids[1] = 0;
				ids[2] = 4;
				ids[3] = 7;
				break;
			case 5:
				ids[0] = 4;
				ids[1] = 5;
				ids[2] = 6;
				ids[3] = 7;
				break;

			default:
				break;
			}
			return rect_type(_points[ids[0]], _points[ids[1]], _points[ids[2]], _points[ids[3]]);
		}

		bool hasIntersectionPoint(const edge_type& segment) const {
			vec3_type intersectionPoint;
			return getIntersectionPoint(segment, intersectionPoint);
		}

		bool getIntersectionPoint(const edge_type& segment, vec3_type& intersectionPoint) const {
			bool tag = false;
			for (int i = 0; i < NumFaces; i++) {
				rect_type rect = getRect(i);
				tag = rect.getIntersectionPoint(segment, intersectionPoint);
				if (tag) {
					break;
				}
			}
			return tag;
		}

		bool beIntersected(const Cuboid_T& cuboid) {
			edge_type edge;
			for (int i = 0; i < NumEdges; i++) {
				edge = cuboid.getEdge(i);
				if (hasIntersectionPoint(edge))
					return true;
			}
			return false;
		}

		vec3_type& operator [](int id) {
			return _points[id];
		}

	private:
		//vec3_type _points[N];
		std::array<vec3_type, N> _points;
	};
	


}


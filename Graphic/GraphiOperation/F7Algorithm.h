#ifndef F7ALGORITHM_H
#define F7ALGORITHM_H

#include "F7Cuboid.h"
#include "F7Plane.h"
#include "F7ConvexPolygon.h"
#include "F7Math.h"
#include "F7/Vec/Vec.h"

namespace F7 {



template <typename T>
float GetDistPointToLine(const T& point, const T& linePoint1, const T& linePoint2)
{
    return ((linePoint1 - point) ^ (linePoint2 - point)).length() / (linePoint2 - linePoint1).length();
}

template <typename T, typename U>
bool IsIntersectant(const F7Cuboid<T>& cuboid1, const F7Cuboid<T>& cuboid2)
{
    //std::vector<T> vecCuboid1 = cuboid1.asStdVector();
    std::vector<F7ConvexPolygon<T>> vecPoly;
    F7ConvexPolygon<T> poly;

    poly.push_back(cuboid1[0]);
    poly.push_back(cuboid1[1]);
    poly.push_back(cuboid1[5]);
    poly.push_back(cuboid1[4]);
    poly.init();
    vecPoly.push_back(poly);
    poly.clear();

    poly.push_back(cuboid1[3]);
    poly.push_back(cuboid1[2]);
    poly.push_back(cuboid1[6]);
    poly.push_back(cuboid1[7]);
    poly.init();
    vecPoly.push_back(poly);
    poly.clear();

    poly.push_back(cuboid1[0]);
    poly.push_back(cuboid1[3]);
    poly.push_back(cuboid1[7]);
    poly.push_back(cuboid1[4]);
    poly.init();
    vecPoly.push_back(poly);
    poly.clear();

    poly.push_back(cuboid1[1]);
    poly.push_back(cuboid1[2]);
    poly.push_back(cuboid1[6]);
    poly.push_back(cuboid1[5]);
    poly.init();
    vecPoly.push_back(poly);
    poly.clear();

    for (int i=0; i<4; ++i)
        poly.push_back(cuboid1[i]);
    poly.init();
    vecPoly.push_back(poly);
    poly.clear();

    for (int i=4; i<8; ++i)
        poly.push_back(cuboid1[i]);
    poly.init();
    vecPoly.push_back(poly);
    poly.clear();


    std::vector<std::array<T,2>> segments;
    segments.push_back({cuboid2[0], cuboid2[1]});
    segments.push_back({cuboid2[1], cuboid2[2]});
    segments.push_back({cuboid2[2], cuboid2[3]});
    segments.push_back({cuboid2[3], cuboid2[0]});

	segments.push_back({ cuboid2[4], cuboid2[5] });
	segments.push_back({ cuboid2[5], cuboid2[6] });
	segments.push_back({ cuboid2[6], cuboid2[7] });
	segments.push_back({ cuboid2[7], cuboid2[4] });

    segments.push_back({cuboid2[0], cuboid2[4]});
    segments.push_back({cuboid2[1], cuboid2[5]});
    segments.push_back({cuboid2[2], cuboid2[6]});
    segments.push_back({cuboid2[3], cuboid2[7]});


    for (auto& segment : segments)
    {
        for (auto& ply : vecPoly)
        {
            if ( ply.existCrosspointWithLineSegment<U>(segment[0], segment[1]) )
                return true;
        }
    }
    return false;
}




template <typename T, typename U>
bool IsIntersectant(const T& start, const T& end, const F7Cuboid<T>& cuboid)
{
	std::vector<F7ConvexPolygon<T>> vecPoly;
	F7ConvexPolygon<T> poly;

	poly.push_back(cuboid[0]);
	poly.push_back(cuboid[1]);
	poly.push_back(cuboid[5]);
	poly.push_back(cuboid[4]);
	poly.init();
	vecPoly.push_back(poly);
	poly.clear();

	poly.push_back(cuboid[3]);
	poly.push_back(cuboid[2]);
	poly.push_back(cuboid[6]);
	poly.push_back(cuboid[7]);
	poly.init();
	vecPoly.push_back(poly);
	poly.clear();

	poly.push_back(cuboid[0]);
	poly.push_back(cuboid[3]);
	poly.push_back(cuboid[7]);
	poly.push_back(cuboid[4]);
	poly.init();
	vecPoly.push_back(poly);
	poly.clear();

	poly.push_back(cuboid[1]);
	poly.push_back(cuboid[2]);
	poly.push_back(cuboid[6]);
	poly.push_back(cuboid[5]);
	poly.init();
	vecPoly.push_back(poly);
	poly.clear();

	for (int i = 0; i < 4; ++i)
		poly.push_back(cuboid[i]);
	poly.init();
	vecPoly.push_back(poly);
	poly.clear();

	for (int i = 4; i < 8; ++i)
		poly.push_back(cuboid[i]);
	poly.init();
	vecPoly.push_back(poly);
	poly.clear();

	for (auto& ply : vecPoly)
	{
		if (ply.existCrosspointWithLineSegment<U>(start, end))
			return true;
	}
	return false;
}

}//namespace F7
#endif // F7ALGORITHM_H

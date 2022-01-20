#ifndef F7CONVEXPOLYGON_H
#define F7CONVEXPOLYGON_H

#include <vector>
#include <cmath>

#include "F7Math.h"
#include "F7Plane.h"
//#include "F7Algorithm.h"

namespace F7 {

template <typename T>
class F7ConvexPolygon
{
public:
    F7ConvexPolygon() {}
    F7ConvexPolygon(const std::vector<T>& points) : _points(points) { init(); }

public:
    bool init()
    {
        if (_points.size()>=3)
        {
            _plane = F7Plane<T>(_points[0], _points[1], _points[2]);
            return true;
        }
        return false;
    }

public:
    template <typename U>
    bool pointIsOutside(const T& point);

    template <typename U>
    bool existCrosspointWithLineSegment(const T& point1, const T& point2)
    {
        if (!_plane.existCrosspointWithLineSegment(point1, point2))
            return false;
        T crosspoint;
        _plane.getCrosspointWithLineSegment(point1, point2, crosspoint);
        return !pointIsOutside<U>(crosspoint);
    }

    void push_back(const T& point) { _points.push_back(point); }
    void clear() { _points.clear(); }
    bool valid()
    {
        if (_points.size()<3) return false;
        if (!_plane.valid())
        {
            _plane.initPlane(_points[0], _points[1], _points[2]);
            return _plane.valid();
        }
        else
            return true;
    }



private:
    std::vector<T> _points;
    F7Plane<T> _plane;
};

template <typename T>
    template<typename U>
bool F7ConvexPolygon<T>::pointIsOutside(const T &point)
{
    int n = _points.size();
    if (n<3)
        return true;
    U sumRadian {0};
    for (int i=0; i<n-1; ++i)
    {
        T& point1 = _points[i];
        T& point2 = _points[i+1];
        T direct1 = point1 - point;
        T direct2 = point2 - point;
        U len1 = direct1.length();
        U len2 = direct2.length();
        if (len1 == 0 || len2 == 0)
            return false;
        sumRadian += acos(direct1*direct2/len1/len2);
    }
    {
        T& point1 = _points[n-1];
        T& point2 = _points[0];
        T direct1 = point1 - point;
        T direct2 = point2 - point;
        U len1 = direct1.length();
        U len2 = direct2.length();
        if (len1 == 0 || len2 == 0)
            return false;
        sumRadian += acos(direct1*direct2/len1/len2);
    }
    //if (sumRadian == PI*2)
    if (F7Equal(sumRadian, PI*2))
        return false;
    return true;
}

}//namespace F7
#endif // F7CONVEXPOLYGON_H

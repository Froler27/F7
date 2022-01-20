#include "F7Plane.h"
#include "F7VectorOperation.h"
#include <cmath>
#include "F7/Vec/Vec.h"

//#include <osg/Vec3f>
//#include <osg/Vec3d>

namespace F7 {

template class F7Plane<Vec3d>;
template class F7Plane<Vec3f>;

template<typename T>
ERelPointAndPlane F7Plane<T>::GetRelationshipPointAndPlane(const T &point, const T &point1, const T &point2, const T &point3)
{
    F7Plane<T> plane(point1, point2, point3);
    return plane.getRelationshipWithPoint(point);
}

template<typename T>
F7Plane<T>::F7Plane(const T& point1, const T& point2, const T& point3)
{
    initPlane(point1,point2,point3);
}

template<typename T>
F7Plane<T>::F7Plane(const T& direct, const T& point)
    : _direct(direct), _point(point)
{
    init();
}

template<typename T>
F7Plane<T>::F7Plane(const T& direct)
    : _direct(direct)
{
    init();
}

template<typename T>
void F7Plane<T>::initPlane(const T &point1, const T &point2, const T &point3)
{
    _point = point1;
    T direct1 = point2 - point1;
    T direct2 = point3 - point1;

    EAngleType angleType = F7VectorOperation<T>::GetAngelType(direct1, direct2);
    if (angleType != EAngleType::ZERO && angleType != EAngleType::STRAIGHT)
        _direct = direct1^direct2;

    init();
}

template<typename T>
ERelPointAndPlane F7Plane<T>::getRelationshipWithPoint(const T &point) const
{
    if (!valid())
        return ERelPointAndPlane::UNKNOWN;
    EAngleType angleType = F7VectorOperation<T>::GetAngelType(_direct, point-_point);
    if (angleType == EAngleType::RIGHT)
        return ERelPointAndPlane::ON;
    else if (EAngleType::ZERO == angleType || EAngleType::ACUTE == angleType)
        return ERelPointAndPlane::ABOVE;
    else
        return ERelPointAndPlane::BELOW;
}

//template<typename T>
//bool F7Plane<T>::twoPointsIsInSameSide(const T &point1, const T &point2)
//{
//    ERelPointAndPlane rel1 = getRelationshipWithPoint(point1);
//    ERelPointAndPlane rel2 = getRelationshipWithPoint(point2);
//    if (rel1 == ERelPointAndPlane::UNKNOWN || rel2 == ERelPointAndPlane::UNKNOWN)
//        return true;
//    if (rel1 == rel2)
//        return true;
//    return false;
//}

template<typename T>
bool F7Plane<T>::existCrosspointWithStraightLine(const T &point1, const T &point2) const
{
    if (point1 == point2 || !valid())
        return false;
    T abc = point2 - point1;
    if (abc*_direct == 0)
    {
        // if plane is valid, getRelationshipWithPoint will not return UNKNOWN
        if (ERelPointAndPlane::ON == getRelationshipWithPoint(point1))
            return true;
        return false;
    }
    return true;
}

template<typename T>
bool F7Plane<T>::existCrosspointWithLineSegment(const T &point1, const T &point2) const
{
    if (point1 == point2 || !valid())
        return false;
    ERelPointAndPlane rel1 = getRelationshipWithPoint(point1);
    ERelPointAndPlane rel2 = getRelationshipWithPoint(point2);
    if (rel1 == rel2)
    {
        if (rel1 == ERelPointAndPlane::ON)
            return true;
        return false;
    }
    return true;
}

template<typename T>
bool F7Plane<T>::getCrosspointWithStraightLine(const T &point1, const T &point2, T &resPoint) const
{
    if (point1 == point2 || !valid())
        return false;
    T abc = point2 - point1;
    auto tem = abc * _direct;
    if (tem == 0)
    {
        // if plane is valid, getRelationshipWithPoint will not return UNKNOWN
        if (ERelPointAndPlane::ON == getRelationshipWithPoint(point1))
        {
			// NOTE: _point is not on straight line, this can use to judge line whether on plane;
			resPoint = _point;
            return true;
        }
        return false;
    }
    else {
        auto tt = -(_K + point1*_direct) / tem;
        resPoint = point1 + abc * tt;
        return true;
    }
    resPoint = point1;

    if (abc.x() == 0)
    {
        if (abc.y() == 0)
            resPoint.z() = -(_K+_direct.x()*point1.x()+_direct.y()*point1.y())/_direct.z();
        else if (abc.z() == 0)
            resPoint.y() = -(_K+_direct.x()*point1.x()+_direct.z()*point1.z())/_direct.y();
        else
        {
            // y = (c*C/b * y1 - A*x1 - C*z1 - K)/(c*C/b + B)
            resPoint.y() = ( (abc.z()*_direct.z()/abc.y())*point1.y() - _direct.x()*point1.x() - _direct.z()*point1.z() - _K)/
                    (_direct.y()+(abc.z()*_direct.z()/abc.y()));
            // z = z1 + c/b*(y-y1);
            resPoint.z() = point1.z() + abc.z()/abc.y()*(resPoint.y()-point1.y());
        }
    }
    else if (abc.y() == 0)
    {
        if (abc.z() == 0)
            resPoint.x() = -(_K+_direct.y()*point1.y()+_direct.z()*point1.z())/_direct.x();
        else
        {
            // x = (c*C/a * x1 - B*y1 - C*z1 - K)/(c*C/a + A)
            resPoint.x() = ( (abc.z()*_direct.z()/abc.x())*point1.x() - _direct.y()*point1.y() - _direct.z()*point1.z() - _K)/
                    (_direct.x()+(abc.z()*_direct.z()/abc.x()));
            // z = z1 + c/a*(x-x1);
            resPoint.z() = point1.z() + abc.z()/abc.x()*(resPoint.x()-point1.x());
        }
    }
    else if (abc.z() == 0)
    {
        // x = (b*B/a * x1 - B*y1 - C*z1 - K)/(b*B/a + A)
        resPoint.x() = ( (abc.y()*_direct.y()/abc.x())*point1.x() - _direct.y()*point1.y() - _direct.z()*point1.z() - _K)/
                (_direct.x()+(abc.y()*_direct.y()/abc.x()));
        // y = y1 + b/a*(x-x1);
        resPoint.y() = point1.y() + abc.y()/abc.x()*(resPoint.x()-point1.x());
    }
    else
    {
        // x = ( (B*b+C*c)/a*x1 - B*y1 - C*z1 - K )/(A + (B*b+C*c)/a)
        resPoint.x() = ( (_direct.y()*abc.y() + _direct.z()*abc.z())/abc.x()*_point.x() -
                         _direct.y()*_point.y() - _direct.z()*_point.z() - _K ) /
                ( _direct.x() + (_direct.y()*abc.y() + _direct.z()*abc.z())/abc.x() );
        // y = y1 + b/a*(x-x1)
        resPoint.y() = point1.y() + abc.y()/abc.x()*(resPoint.x()-point1.x());
        // z = z1 + c/a*(x-x1);
        resPoint.z() = point1.z() + abc.z()/abc.x()*(resPoint.x()-point1.x());
    }
    return true;
}

template<typename T>
bool F7Plane<T>::getCrosspointWithLineSegment(const T &point1, const T &point2, T &resPoint) const
{
    if (!existCrosspointWithLineSegment(point1, point2))
        return false;
    return getCrosspointWithStraightLine(point1, point2, resPoint);
}

template<typename T>
bool F7Plane<T>::valid() const
{
    if (_direct.x()==0 && _direct.y()==0 && _direct.z()==0)
        return false;
    else
        return true;
}

template<typename T>
void F7Plane<T>::init()
{
    _direct.normalize();
    _K = -(_direct*_point);
}


}//namespace F7

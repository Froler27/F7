#include "F7VectorOperation.h"
#include "F7Math.h"
#include <cmath>

#include "F7/Vec/Vec.h"

//#include <osg/Vec3f>
//#include <osg/Vec3d>

namespace F7 {

template class F7VectorOperation<Vec3d>;
template class F7VectorOperation<Vec3f>;

template<typename T>
double F7VectorOperation<T>::GetAngelRadian(const T &vectorL, const T &vectorR)
{
    double lenL = vectorL.length();
    double lenR = vectorR.length();
    if (lenL==0. || lenR==0)
        return 0.;
    return acos(vectorL*vectorR/lenL/lenR);
}

template<typename T>
EAngleType F7VectorOperation<T>::GetAngelType(const T &vectorL, const T &vectorR)
{
    double radian = GetAngelRadian(vectorL, vectorR);
    if (radian == 0)
        return EAngleType::ZERO;
    else if (radian < PI_2)
        return EAngleType::ACUTE;
    else if (radian == PI_2)
        return EAngleType::RIGHT;
    else if (radian < PI)
        return EAngleType::OBTUSE;
    else
        return EAngleType::STRAIGHT;
}

}// namespace F7

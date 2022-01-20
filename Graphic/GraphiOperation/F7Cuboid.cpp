#include "F7Cuboid.h"
#include "F7Plane.h"
#include "F7/Vec/Vec.h"

#include <cmath>

//#include <osg/Vec3f>
//#include <osg/Vec3d>

namespace F7 {

	template class F7Cuboid<Vec3d>;
	template class F7Cuboid<Vec3f>;


//template<typename TVector>
//F7Cuboid<TVector>::F7Cuboid(const TVector& vetexArr)
//    : _vetexArr(vetexArr), _vetexArrayValid(true)
//{
//    _lwh.x() = fabs(_vetexArr[1] - _vetexArr[0]);
//    _lwh.y() = fabs(_vetexArr[3] - _vetexArr[0]);
//    _lwh.z() = fabs(_vetexArr[4] - _vetexArr[0]);
//}

template<typename TVector>
F7Cuboid<TVector>::F7Cuboid(const TVector &lwh, const TVector &direct, const TVector &center)
    : _center(center), _lwh(lwh), _direct(direct)
{
    init();
}

template<typename TVector>
void F7Cuboid<TVector>::init()
{
    _outside = ERelPointAndPlane::ABOVE;
}

// TODO: need matrix to realize pose translate
template<typename TVector>
void F7Cuboid<TVector>::generateVetexes()
{
	if (_vetexArrayValid)
		return;
	double len = _lwh.x() / 2;
	double wid = _lwh.y() / 2;
	double hei = _lwh.z() / 2;
	_vetexArr[0] = TVector( _center.x() - len, _center.y() - wid, _center.z() - hei );
	_vetexArr[1] = TVector( _center.x() + len, _center.y() - wid, _center.z() - hei );
	_vetexArr[2] = TVector( _center.x() + len, _center.y() + wid, _center.z() - hei );
	_vetexArr[3] = TVector( _center.x() - len, _center.y() + wid, _center.z() - hei );
	_vetexArr[4] = TVector( _center.x() - len, _center.y() - wid, _center.z() + hei );
	_vetexArr[5] = TVector( _center.x() + len, _center.y() - wid, _center.z() + hei );
	_vetexArr[6] = TVector( _center.x() + len, _center.y() + wid, _center.z() + hei );
	_vetexArr[7] = TVector( _center.x() - len, _center.y() + wid, _center.z() + hei );

    _vetexArrayValid = true;
}

template<typename TVector>
bool F7Cuboid<TVector>::isOutSide(ERelPointAndPlane rel) const
{
    if (rel == _outside || rel == ERelPointAndPlane::UNKNOWN)
        return true;
    return false;
}

template<typename TVector>
bool F7Cuboid<TVector>::pointIsOutside(const TVector &point) const
{
    if (!valid())
        return true;
    ERelPointAndPlane rel1, rel2;
    rel1 = F7Plane<TVector>::GetRelationshipPointAndPlane(point, _vetexArr[0], _vetexArr[4], _vetexArr[3]);
    rel2 = F7Plane<TVector>::GetRelationshipPointAndPlane(point, _vetexArr[6], _vetexArr[5], _vetexArr[2]);
    bool bOut1 = isOutSide(rel1);
    bool bOut2 = isOutSide(rel2);
    if (bOut1 != bOut2) return true;
    rel2 = F7Plane<TVector>::GetRelationshipPointAndPlane(point, _vetexArr[0], _vetexArr[1], _vetexArr[4]);
    bOut2 = isOutSide(rel2);
    if (bOut1 != bOut2) return true;
    rel2 = F7Plane<TVector>::GetRelationshipPointAndPlane(point, _vetexArr[6], _vetexArr[2], _vetexArr[7]);
    bOut2 = isOutSide(rel2);
    if (bOut1 != bOut2) return true;
    rel2 = F7Plane<TVector>::GetRelationshipPointAndPlane(point, _vetexArr[0], _vetexArr[3], _vetexArr[1]);
    bOut2 = isOutSide(rel2);
    if (bOut1 != bOut2) return true;
    rel2 = F7Plane<TVector>::GetRelationshipPointAndPlane(point, _vetexArr[6], _vetexArr[7], _vetexArr[5]);
    bOut2 = isOutSide(rel2);
    if (bOut1 != bOut2) return true;
    return false;
}

template<typename TVector>
bool F7Cuboid<TVector>::isIntersectant(F7Cuboid &cuboid) const
{
    for (int i=0; i<VetexArrayNum; i++)
    {
        if (!pointIsOutside(cuboid[i]))
            return true;
    }
    return false;
}

template<typename TVector>
bool F7Cuboid<TVector>::valid() const
{
    if (_lwh.x() == 0 || _lwh.y() == 0 || _lwh.z() == 0 )
        return false;
    else
        return true;
}


//template<typename TVector>
//void F7Cuboid<TVector>::setLength(TVector::value_type len)
//{
//    if (len == _lwh.x())
//        return;
//    _vetexArrayValid = false;
//    _lwh.x() = len;
//}

//template<typename TVector>
//void F7Cuboid<TVector>::setWidth(TVector::value_type wid)
//{
//    if (wid == _lwh.y())
//        return;
//    _vetexArrayValid = false;
//    _lwh.y() = wid;
//}

//template<typename TVector>
//void F7Cuboid<TVector>::setHeight(TVector::value_type hei)
//{
//    if (hei == _lwh.z())
//        return;
//    _vetexArrayValid = false;
//    _lwh.z() = hei;
//}

template<typename TVector>
void F7Cuboid<TVector>::setLWH(const TVector &lwh)
{
    if (lwh == _lwh)
        return;
    _vetexArrayValid = false;
    _lwh = lwh;
}

template<typename TVector>
void F7Cuboid<TVector>::setCenter(const TVector &center)
{
    if (_center == center)
        return;
    _vetexArrayValid = false;
    _center = center;
}


}//namespace F7

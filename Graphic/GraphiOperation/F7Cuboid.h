#ifndef F7CUBOID_H
#define F7CUBOID_H

#include <array>
#include <vector>

namespace F7 {

enum class ERelPointAndPlane;

template <typename TVector>
class F7Cuboid
{
public:
    typedef std::array<TVector, 8> CuboidVetexArray;
    static const int VetexArrayNum {8};

public:
    explicit F7Cuboid(const CuboidVetexArray& vetexArr);
    explicit F7Cuboid(const TVector& lwh={0,0,0}, const TVector& direct={0,1,0}, const TVector& center={0,0,0});
private:
    void init();

public:
    void generateVetexes();
    CuboidVetexArray& getVetexArr() { return _vetexArr; }
    const CuboidVetexArray& getVetexArr() const { return _vetexArr; }

    bool isOutSide(ERelPointAndPlane rel) const;
    bool pointIsOutside(const TVector& point) const;
    bool isIntersectant(F7Cuboid& cuboid) const;


public:
    bool valid() const;

    TVector& operator [](int id)
    {
        return _vetexArr[id];
    }
    const TVector& operator [](int id) const
    {
        return _vetexArr[id];
    }

    std::vector<TVector> asStdVector()
    {
        std::vector<TVector> vec;
        for (auto& x:_vetexArr) vec.push_back(x);
        return vec;
    }

    //void setLength(TVector::value_type len);
    //auto getLength(TVector v=TVector()) const -> decltype( (v.x())+0 ) { return _lwh.x(); }

//    void setWidth(TVector::value_type wid);
//    TVector::value_type getWidth() const { return _lwh.y(); }

//    void setHeight(TVector::value_type hei);
//    TVector::value_type getHeight() const { return _lwh.z(); }

    void setLWH(const TVector& lwh);
    const TVector& getLWH() const { return _lwh; }

    void setCenter(const TVector& center);
    const TVector& getCenter() const { return _center; }

private:
    TVector _center {0,0,0};
    TVector _lwh {0,0,0};//length, width, height corresponding to x, y, z
    TVector _direct {0,1,0};
    CuboidVetexArray _vetexArr;
    bool _vetexArrayValid { false };
    ERelPointAndPlane _outside;
};

}//namespace F7

#endif // F7CUBOID_H

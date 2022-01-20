#ifndef F7PLANE_H
#define F7PLANE_H

namespace F7 {

/**
 * @brief The ERelPointPlane enum is the relationship between a point and a plane
 */
enum class ERelPointAndPlane {
    ABOVE,  // the point is above the plane
    ON,     // the point is on the plane
    BELOW,  // the point is below the plane
    UNKNOWN // the plane is invalid
};
/**
 * @note: T is 3D vector type that need to have
 *      1. operator^() multiplication cross
 *      2. operator*() +() -()
 *      3. .x() .y() .z()
 */
template <typename T>
class F7Plane
{
public:
    /**
     * @note: the direction of the plane is determined by the right hand rule.
     *  planePoint1 2 3 are arranged counterclockwise when you look at them from the top
     *  of the plane.
     */
    static ERelPointAndPlane GetRelationshipPointAndPlane(const T& point, const T& point1, const T& point2, const T& point3);

public:
    F7Plane(const T& point1, const T& point2, const T& point3);
    F7Plane(const T& direct, const T& point);
    explicit F7Plane(const T& direct);
    F7Plane() {}
    void initPlane(const T& point1, const T& point2, const T& point3);

    ERelPointAndPlane getRelationshipWithPoint(const T& point) const;
    //bool twoPointsIsInSameSide(const T& point1, const T& point2);
    bool existCrosspointWithStraightLine(const T& point1, const T& point2) const;
    bool existCrosspointWithLineSegment(const T& point1, const T& point2) const;
    bool getCrosspointWithStraightLine(const T& point1, const T& point2, T& resPoint) const;
    bool getCrosspointWithLineSegment(const T& point1, const T& point2, T& resPoint) const;


    bool valid() const;

private:
    void init();

private:
    T _direct {0,0,0};
    T _point {0,0,0};
    double _K {0};
};

}//namespace F7


#endif // F7PLANE_H

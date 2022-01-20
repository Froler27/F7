#ifndef F7VECTOROPERATION_H
#define F7VECTOROPERATION_H

namespace F7 {

enum class EAngleType {
    ZERO,
    ACUTE,
    RIGHT,
    OBTUSE,
    STRAIGHT
};

/**
 * @details T is vector type that need
 *      1. overload operator*()
 *      2. .length()
 */
template <typename T>
class F7VectorOperation
{
public:
    static double GetAngelRadian(const T& vectorL, const T& vectorR);
    static EAngleType GetAngelType(const T& vectorL, const T& vectorR);

public:
    F7VectorOperation() {}
};


}// namespace F7
#endif // F7VECTOROPERATION_H

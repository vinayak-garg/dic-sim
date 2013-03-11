#ifndef UTILITY_H
#define UTILITY_H

namespace math{

template<typename T>
inline T min(T a, T b)
{
    return a > b ? b : a;
}

template<typename T>
inline T max(T a, T b)
{
    return a > b ? a : b;
}

template<typename T>
inline T abs(T a)
{
    return a < 0 ? -a : a;
}

}
#endif // UTILITY_H

#include <typeindex>

typedef std::type_index TypeIndex;

template<typename T>
inline TypeIndex getTypeIndex()
{
    return std::type_index(typeid(T));
}
#include <typeindex>

typedef std::type_index TypeIndex;

template<typename T>
TypeIndex getTypeIndex();
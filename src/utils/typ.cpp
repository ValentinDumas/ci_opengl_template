//
// Created by Spark on 07/05/2019.
//

#include "typ.h"

template <typename T>
TypeIndex getTypeIndex()
{
    return std::type_index(typeid(T));
}
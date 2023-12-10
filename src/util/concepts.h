//
// Created by Jan Bednář on 04.11.2023.
//

#ifndef CV1_CONCEPTS_H
#define CV1_CONCEPTS_H

#include <concepts>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

#endif //CV1_CONCEPTS_H

//
// Created on 2024/2/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include <aki/include/aki/jsbind.h>
#include "CppEngine.h"

JSBIND_ADDON(entry);

JSBIND_CLASS(CppEngine) {
    JSBIND_CONSTRUCTOR<std::string>();
    JSBIND_METHOD(setDbPath);
    JSBIND_METHOD(toString);
    JSBIND_METHOD(testCallback);
}
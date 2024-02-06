//
// Created on 2024/2/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef MyOhosAkiDemo_CppEngine_H
#define MyOhosAkiDemo_CppEngine_H

#include <string>
#include "OhosAkiDefine.h"

class CppEngine {
    // 生命周期
    public:
        OHOS_AKI_API CppEngine(std::string key);
        ~CppEngine() = default;
    
    // 对外接口
    public:
        OHOS_AKI_API void setDbPath(std::string db_path);
        OHOS_AKI_API void toString();
        OHOS_AKI_API void testCallback(std::string value,std::function<void(std::string)> func);
    
    // 私有字段
    private:
        std::string key_;
        std::string db_path_;
};

#endif //MyOhosAkiDemo_CppEngine_H

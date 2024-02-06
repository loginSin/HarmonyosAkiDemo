//
// Created on 2024/2/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "CppEngine.h"
#include "hilog/log.h"

OHOS_AKI_API CppEngine::CppEngine(std::string key) {
    this->key_ = key;
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "constructor key: %{public}s",key.c_str());
}

OHOS_AKI_API void CppEngine::setDbPath(std::string db_path) {
    this->db_path_ = db_path;
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "setDbPath db_path: %{public}s",db_path.c_str());
}

OHOS_AKI_API void CppEngine::toString() {
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "key: %{public}s, dbPath: %{public}s",this->key_.c_str(), this->db_path_.c_str());
}

OHOS_AKI_API void CppEngine::testCallback(std::string value,std::function<void(std::string)> func) {
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "testCallback value: %{public}s",value.c_str());
    if (func != nullptr) {
        func(value + " testCallback result");
    }
}
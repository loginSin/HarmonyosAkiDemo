# 鸿蒙 AKI Demo

[AKI](https://gitee.com/openharmony-sig/aki) (Alpha Kernel Interacting) 是一款边界性编程体验友好的 ArkTs FFI 开发框架，针对 OpenHarmony Native 开发提供 JS 与 C/C++ 跨语言访问场景解决方案。

本项目是 AKI 的 Demo 项目，演示了如何使用 AKI 进行 JS 与 C/C++ 交互。

# 1. 导入 AKI

本项目以 AKI 推荐的手动方式导入，详细见：https://gitee.com/openharmony-sig/aki#-%E5%BF%AB%E9%80%9F%E6%8E%A5%E5%85%A5-

# 2. 定义 AKI API

C++ 的类会有很多方法，一些会被其他 C++ 模块调用，一些要被 AKI 的 JS 层调用。需要定义一个宏，用来标记哪些方法是 AKI 的 JS 层调用的。

```cpp
// OhosAkiDefine.h

// 建议对外接口使用该注解声明
#define OHOS_AKI_API

```

# 3. 编写 C++ 类
    
```cpp
// CppEngine.h
#include <string>
#include "OhosAkiDefine.h"

class CppEngine {
    // 生命周期
    public:
        // 构造方法，需要 JS 层调用
        OHOS_AKI_API CppEngine(std::string key);
        ~CppEngine() = default;
    
    // 对外接口
    public:
        // 设置路径方法，需要 JS 层调用
        OHOS_AKI_API void setDbPath(std::string db_path);
        // toString 方法，需要 JS 层调用
        OHOS_AKI_API void toString();
        // 带 Callback 方法，需要 JS 层调用
        OHOS_AKI_API void testCallback(std::string value,std::function<void(std::string)> func);
    
    // 私有字段
    private:
        std::string key_;
        std::string db_path_;
};
```

```cpp
// CppEngine.cpp
#include "CppEngine.h"
#include "hilog/log.h"

// 构造方法，需要 JS 层调用
OHOS_AKI_API CppEngine::CppEngine(std::string key) {
    this->key_ = key;
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "constructor key: %{public}s",key.c_str());
}

// 设置路径方法，需要 JS 层调用
OHOS_AKI_API void CppEngine::setDbPath(std::string db_path) {
    this->db_path_ = db_path;
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "setDbPath db_path: %{public}s",db_path.c_str());
}

// toString 方法，需要 JS 层调用
OHOS_AKI_API void CppEngine::toString() {
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "key: %{public}s, dbPath: %{public}s",this->key_.c_str(), this->db_path_.c_str());
}

// 带 Callback 方法，需要 JS 层调用
OHOS_AKI_API void CppEngine::testCallback(std::string value,std::function<void(std::string)> func) {
    OH_LOG_Print(LOG_APP, LOG_INFO, 1,"CppEngine-cpp", "testCallback value: %{public}s",value.c_str());
    if (func != nullptr) {
        func(value + " testCallback result");
    }
}
```

# 4. 使用 JSBind 绑定

```cpp
// OhosAkiAdapter.cpp
#include <aki/include/aki/jsbind.h>
#include "CppEngine.h"

// 此处的二进制名字为 entry
JSBIND_ADDON(entry);

// 绑定 C++ 类
JSBIND_CLASS(CppEngine) {
    // 绑定 C++ 类构造方法
    JSBIND_CONSTRUCTOR<std::string>();
    // 绑定设置路径方法
    JSBIND_METHOD(setDbPath);
    // 绑定 toString 方法
    JSBIND_METHOD(toString);
    // 绑定带 Callback 方法
    JSBIND_METHOD(testCallback);
}
```

# 5. CMakeLists.txt 中添加 cpp

```cmake
# CMakeLists.txt

# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(MyOhosAkiDemo)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
# 增加 aki 的依赖
add_subdirectory(aki)
include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

# 增加各个 cpp 文件
add_library(entry SHARED CppEngine.cpp OhosAkiAdapter.cpp)

# 增加 aki_jsbind 依赖
target_link_libraries(entry PUBLIC libace_napi.z.so aki_jsbind)
```

# 6. 声明 JS 接口

此步如果不做，在 JS 层找不到对应的方法。

```js
// types/libentry/index.d.ts
export class CppEngine {
  constructor(key: string);
  setDbPath:(db_path: string) => void;
  toString:() => void;
  testCallback:(value: string, func:(result:string) => void) => void;
}

```

# 7. 使用 JS 调用 C++ 方法

```js
// ets/pages/Index.ets

Button("创建")
    .fontSize(50)
    .fontWeight(FontWeight.Bold)
    .onClick(() => {
    this.engine = new testNapi.CppEngine("testKey");
    hilog.info(0x0000, 'CppEngine-js', '创建');
})
Button("设置路径")
    .fontSize(50)
    .fontWeight(FontWeight.Bold)
    .onClick(() => {
    this.engine.setDbPath("path/to/db");
    hilog.info(0x0000, 'CppEngine-js', '设置路径');
})
Button("打印信息")
    .fontSize(50)
    .fontWeight(FontWeight.Bold)
    .onClick(() => {
    this.engine.toString();
    hilog.info(0x0000, 'CppEngine-js', '打印信息');
})
Button("调用Callback")
    .fontSize(50)
    .fontWeight(FontWeight.Bold)
    .onClick(() => {
    hilog.info(0x0000, 'CppEngine-js', '调用Callback接口');
    this.engine.testCallback("testValue",(result) => {
        hilog.info(0x0000, 'CppEngine-js', 'Callback回调结果 ' + result);
    });
})
```
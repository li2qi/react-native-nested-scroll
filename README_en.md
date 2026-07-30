> Template Version: v0.4.1

<p align="center">
  <h1 align="center"> <code>react-native-nested-scroll</code> </h1>
</p>

This project is developed based on [react-native-nested-scroll@0.14.0](https://github.com/sdcxtech/react-native-troika/tree/master/packages/nested-scroll).

| Name    | Version    | Release Information     | Supported RN Version    | Supported Autolink     | Compile API Version     | Community Baseline Version    | npm Address                |
| ----------------------------------------------- | ---------------- | --------------------------------------------------------------------------- | --------------- | -------- | ------- | ------ | ------------------------------------------------------------------------------------------ |
| @react-native-oh-tpl/react-native-nested-scroll | ~0.14.2  | [Github Releases](https://github.com/react-native-oh-library/react-native-nested-scroll/releases) | 0.72  | 否 | API12+ | 0.14.0 | [Npm Address](https://www.npmjs.com/package/@react-native-oh-tpl/react-native-nested-scroll) |


## Installation and Usage

Please go to the Releases release address of the third-party library to view the supporting version information: [@react-native-oh-tpl/react-native-nested-scroll Releases](https://github.com/react-native-oh-library/react-native-nested-scroll/releases). For older versions that are not published to npm, install the tgz package by referring to the [Installation Guide](/en-us/tgz-usage.md).

Navigate to your project directory and enter the following command:

<!-- tabs:start -->

#### **npm**

```bash
npm install @react-native-oh-tpl/react-native-nested-scroll
```

#### **yarn**

```bash
yarn add @react-native-oh-tpl/react-native-nested-scroll
```

<!-- tabs:end -->

## Link

|                                      | Is supported autolink  | Supported RN Version |
|--------------------------------------|-----------------------|----------------------|
| ~0.14.2                              |  No              |  0.72     |

this step is a guide to manually configure native dependencies.

First, use DevEco Studio to open the HarmonyOS project `harmony` in the project directory.

### 1. Overrides RN SDK

To ensure the project depends on the same version of the RN SDK, you need to add an `overrides` field in the `harmony/oh-package.json5` file at the project's root directory. This field should point to the RN SDK version required by the project. The version can be a specific version number, a fuzzy version, a local HAR package, or a source code directory.

For more information about this field, please refer to the [official documentation](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ide-oh-package-json5-V5#zh-cn_topic_0000001792256137_overrides).

```json
{
  "overrides": {
    "@rnoh/react-native-openharmony": "^0.72.38"
  }
}
```

### 2. Importing Native Code

There are currently two methods:

- By importing HAR packages;
- By directly linking the source code.

Method 1: Importing via HAR package (Recommended)

> [!TIP]
> The HAR package is located in the `harmony` folder of the third-party library's installation path.

Open `entry/oh-package.json5` and add the following dependency:

```json
"dependencies": {
    "@react-native-oh-tpl/react-native-nested-scroll": "file:../../node_modules/@react-native-oh-tpl/react-native-nested-scroll/harmony/nested_scroll.har"
  }
```

Click the `sync` button in the top right corner.

Or execute in the terminal:

```bash
cd entry
ohpm install
```

Method 2: Directly linking the source code

> [!TIP]
> To link the source code directly, please refer to the [instructions for linking source code directly](/zh-cn/link-source-code.md).

### 3. Configure CMakeLists and Import NestedScrollViewPackage

Open `entry/src/main/cpp/CMakeLists.txt` and add the following:

```diff
+ set(OH_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/../../../oh_modules")

# RNOH_BEGIN: manual_package_linking_1
+ add_subdirectory("${OH_MODULES}/@react-native-oh-tpl/react-native-nested-scroll/src/main/cpp" ./nested-scroll)
# RNOH_END: manual_package_linking_1

# RNOH_BEGIN: manual_package_linking_2
+ target_link_libraries(rnoh_app PUBLIC rnoh_nested_scroll)
# RNOH_END: manual_package_linking_2
```

Open `entry/src/main/cpp/PackageProvider.cpp` and add the following:

```diff
#include "RNOH/PackageProvider.h"
#include "generated/RNOHGeneratedPackage.h"
+ #include "NestedScrollViewPackage.h"

using namespace rnoh;

std::vector<std::shared_ptr<Package>> PackageProvider::getPackages(Package::Context ctx) {
    return {
      std::make_shared<RNOHGeneratedPackage>(ctx),
+      std::make_shared<NestedScrollViewPackage>(ctx)
    };
}
```
</details>

### Running

Click the `sync` button in the top right corner.

Or execute in the terminal:

```bash
cd entry
ohpm install
```

Then, build and run the project.

## Constraints and Limitations

### Compatibility

To use this repository, you need to use the correct React-Native and RNOH versions. In addition, you need to use DevEco Studio and the ROM on your phone.

Verified in the following versions.
1. RNOH: 0.72.96; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.858; ROM: 6.0.0.112;


## Example

The following code demonstrates the basic usage of this library:

> [!WARNING]
> The import name of the library remains the same when used.

```js
import React from 'react';
import {ScrollView, StyleSheet, Text, View} from 'react-native';
import {NestedScrollView, NestedScrollViewHeader} from '@react-native-oh-tpl/react-native-nested-scroll';

function NestedScrollFlatList() {
  return (
    <NestedScrollView style={styles.coordinator} bounces = {false}>
      <NestedScrollViewHeader stickyHeight={60}>
        <Text style={styles.text}>anchorTest</Text>
        <Text style={styles.text}>anchor</Text>
      </NestedScrollViewHeader>

      <View style={{ height: "90%"}}>

        <ScrollView> 
          <Text style={{ height: 30}}>test1</Text>
          <Text style={{ height: 30}}>test2</Text>
          <Text style={{ height: 30}}>test3</Text>
          <Text style={{ height: 30}}>test4</Text>
          <Text style={{ height: 30}}>test5</Text>
          <Text style={{ height: 30}}>test6</Text>
          <Text style={{ height: 30}}>test7</Text>
          <Text style={{ height: 30}}>test8</Text>
          <Text style={{ height: 30}}>test9</Text>
          <Text style={{ height: 30}}>test10</Text>
          <Text style={{ height: 30}}>test11</Text>
          <Text style={{ height: 30}}>test12</Text>
          <Text style={{ height: 30}}>test13</Text>
          <Text style={{ height: 30}}>test14</Text>
          <Text style={{ height: 30}}>test15</Text>
          <Text style={{ height: 30}}>test16</Text>
          <Text style={{ height: 30}}>test17</Text>
          <Text style={{ height: 30}}>test18</Text>
          <Text style={{ height: 30}}>test19</Text>
          <Text style={{ height: 30}}>test20</Text>
          <Text style={{ height: 30}}>test21</Text>
          <Text style={{ height: 30}}>test22</Text>
          <Text style={{ height: 30}}>test23</Text>
          <Text style={{ height: 30}}>test24</Text>
          <Text style={{ height: 30}}>test25</Text>
          <Text style={{ height: 30}}>test26</Text>
          <Text style={{ height: 30}}>test27</Text>
          <Text style={{ height: 30}}>test28</Text>
          <Text style={{ height: 30}}>test29</Text>
          <Text style={{ height: 30}}>test30</Text>
        </ScrollView>
      </View>
    </NestedScrollView>
  );
}

const styles = StyleSheet.create({
  coordinator: {
    backgroundColor: '#fff',
  },
  content: {
    backgroundColor: '#0000FF',
    justifyContent: 'center',
    alignItems: 'center',
  },
  image: {
    height: 160,
    width: '100%',
  },
  text: {
    lineHeight: 60,
    fontSize: 18,
    color: '#0xCCCCCC',
  },
});
export default NestedScrollFlatList

```

## Available APIs

> [!TIP]
> The "Platform" column indicates the platforms on which these props are supported in the original third-party library.

> [!TIP]
> If the value in the "HarmonyOS Support" column is "yes," it means the prop is supported on the HarmonyOS platform; "no" means it is not supported; "partially" means that some of its features are supported. The usage of this prop is the same on different platforms, and its effect is consistent with that on iOS or Android.

| Name                   | Description                                                                                       | Type    | Required | Platform | HarmonyOS Support |
| ---------------------- | ------------------------------------------------------------------------------------------------- | ------- | -------- | -------- | ----------------- |
| stickyHeight           | The area of the header height will be pinned to the top.                                          | number  | NO       | All      | yes               |
| stickyHeaderBeginIndex | It means that starting with the first few subcomponents, the subassemblies will be pinned to the top. | number  | NO       | All      | yes               |
| bounce                 | Elastic effect.                                                                                   | boolean | NO       | All      | yes               |
| onScroll               | Component callbacks.                                                                              | number  | NO       | All      | yes               |

## Known Issues

None

## Directory Structure

```
/react-native-nested-scroll
├── harmony/                          # HarmonyOS 原生模块代码
│   └── nested_scroll/
│       ├── build-profile.json5       # HarmonyOS 构建配置
│       ├── consumer-rules.txt          # 消费者混淆规则
│       ├── hvigorfile.ts             # HarmonyOS 构建脚本
│       ├── Index.ets                 # ETS 入口文件
│       ├── obfuscation-rules.txt     # 代码混淆规则
│       ├── oh-package.json5          # HarmonyOS 包配置
│       ├── oh-package-lock.json5     # 包锁定文件
│       ├── ts.ts                     # TypeScript 类型定义
│       └── src/
│           ├── main/
│           │   ├── cpp/              # C++ 原生实现 (New Architecture)
│           │   │   ├── CMakeLists.txt
│           │   │   ├── ComponentDescriptors.h
│           │   │   ├── EventEmitters.h / .cpp
│           │   │   ├── NestedScrollViewComponentInstance.h / .cpp
│           │   │   ├── NestedScrollViewEmitRequestHandler.h
│           │   │   ├── NestedScrollViewHeaderComponentInstance.h / .cpp
│           │   │   ├── NestedScrollViewHeaderEmitRequestHandler.h
│           │   │   ├── NestedScrollViewHeaderJSIBinder.h
│           │   │   ├── NestedScrollViewHeaderNapiBinder.h
│           │   │   ├── NestedScrollViewHeaderNode.h / .cpp
│           │   │   ├── NestedScrollViewJSIBinder.h
│           │   │   ├── NestedScrollViewNapiBinder.h
│           │   │   ├── NestedScrollViewNode.h / .cpp
│           │   │   ├── NestedScrollViewPackage.h
│           │   │   ├── Props.h / .cpp
│           │   │   ├── ShadowNodes.h / .cpp
│           │   │   └── States.h / .cpp
│           │   ├── module.json5
│           │   └── resources/        # 国际化资源
│           │       ├── base/element/string.json
│           │       ├── en_US/element/string.json
│           │       └── zh_CN/element/string.json
│           └── test/                 # 测试文件
│               ├── Ability.test.ets
│               ├── List.test.ets
│               └── LocalUnit.test.ets
│   └── nested_scroll.har             # HarmonyOS 归档包
├── src/                              # JS/TS 前端代码
│   ├── index.tsx                     # 主入口，导出 NestedScrollView 和 NestedScrollViewHeader
│   ├── nestedScrollNativeComponent.ts # 定义 NestedScrollView 原生组件 Props 和事件
│   └── NestedScrollViewHeader/
│       ├── index.tsx                 # Header 组件封装
│       └── nestedScrollHeaderNativeComponent.ts # 定义 Header 原生组件 Props 和事件
├── package.json
├── README.md
├── README.OpenSource
└── LICENSE
```

## How to Contribute

使用过程中发现任何问题都可以提交 [Issue](https://gitcode.com/CPF-RN/rntpc_react-native-nested-scroll/issues)，当然，也非常欢迎提交 [PR](https://github.com/react-native-oh-library/react-native-nested-scroll/pulls).

## 6. Open Source License

This project is based on [The MIT License (MIT)](https://github.com/sdcxtech/react-native-troika/blob/master/packages/nested-scroll/LICENSE), feel free to enjoy and participate in open source.
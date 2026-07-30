> 模板版本：v0.4.1

<p align="center">
  <h1 align="center"> <code>react-native-nested-scroll</code> </h1>
</p>

本项目基于 [react-native-nested-scroll@0.14.0](https://github.com/sdcxtech/react-native-troika/tree/master/packages/nested-scroll) 开发。


| 三方库名称                                           | 三方库版本            | 发布信息                                                                        | 支持RN版本          | Autolink | 编译API版本 | 社区基线版本 | npm地址                                                                                      |
| ----------------------------------------------- | ---------------- | --------------------------------------------------------------------------- | --------------- | -------- | ------- | ------ | ------------------------------------------------------------------------------------------ |
| @react-native-oh-tpl/react-native-nested-scroll | ~0.14.2  | [Github Releases](https://github.com/react-native-oh-library/react-native-nested-scroll/releases) | 0.72  | 否 | API12+ | 0.14.0 | [Npm Address](https://www.npmjs.com/package/@react-native-oh-tpl/react-native-nested-scroll) |

## 安装与使用

请到三方库的 Releases 发布地址查看配套的版本信息：[@react-native-oh-tpl/react-native-nested-scroll Releases](https://github.com/react-native-oh-library/react-native-nested-scroll/releases) 。对于未发布到npm的旧版本，请参考[安装指南](./tgz-usage.md)安装tgz包。


进入到工程目录并输入以下命令：

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

|                                      | 是否支持autolink | RN框架版本 |
|--------------------------------------|-----------------------|----------------------|
| ~0.14.2                              |  否              |  0.72     |

此步骤为手动配置原生依赖项的指导

### 1. Overrides RN SDK

为了让工程依赖同一个版本的 RN SDK，需要在工程根目录的 `harmony/oh-package.json5` 添加 overrides 字段，指向工程需要使用的 RN SDK 版本。替换的版本既可以是一个具体的版本号，也可以是一个模糊版本，还可以是本地存在的 HAR 包或源码目录。

关于该字段的作用请阅读[官方说明](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ide-oh-package-json5-V5#zh-cn_topic_0000001792256137_overrides)

```json
{
  "overrides": {
    "@rnoh/react-native-openharmony": "^0.72.38"
  }
}
```

### 2. 引入原生端代码

目前有两种方法：

- 通过 har 包引入；
- 直接链接源码。

方法一：通过 har 包引入（推荐）

> [!TIP] har 包位于三方库安装路径的 `harmony` 文件夹下。

打开 `entry/oh-package.json5`，添加以下依赖

```json
"dependencies": {
    "@react-native-oh-tpl/react-native-nested-scroll": "file:../../node_modules/@react-native-oh-tpl/react-native-nested-scroll/harmony/nested_scroll.har"
  }
```

点击右上角的 `sync` 按钮

或者在终端执行：

```bash
cd entry
ohpm install
```

方法二：直接链接源码

> [!TIP] 如需使用直接链接源码，请参考[直接链接源码说明](/link-source-code.md)

### 3. 配置 CMakeLists 和引入 NestedScrollViewPackage

打开 `entry/src/main/cpp/CMakeLists.txt`，添加：

```diff
+ set(OH_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/../../../oh_modules")

# RNOH_BEGIN: manual_package_linking_1
+ add_subdirectory("${OH_MODULES}/@react-native-oh-tpl/react-native-nested-scroll/src/main/cpp" ./nested-scroll)
# RNOH_END: manual_package_linking_1

# RNOH_BEGIN: manual_package_linking_2
+ target_link_libraries(rnoh_app PUBLIC rnoh_nested_scroll)
# RNOH_END: manual_package_linking_2
```

打开 `entry/src/main/cpp/PackageProvider.cpp`，添加：

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
### 运行

点击右上角的 `sync` 按钮

或者在终端执行：

```bash
cd entry
ohpm install
```

然后编译、运行即可。

## 约束与限制

### 兼容性

要使用此库，需要使用正确的 React-Native 和 RNOH 版本。另外，还需要使用配套的 DevEco Studio 和 手机 ROM。

在以下版本验证通过：
1. RNOH: 0.72.96; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.858; ROM: 6.0.0.112;

## 使用示例

下面的代码展示了这个库的基本使用场景：

> [!WARNING] 使用时 import 的库名不变。

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

## 使用说明

```js
<NestedScrollView style={styles.coordinator} bounces = {false}>
   <NestedScrollViewHeader stickyHeight={60}>
        <Image source={require('../assets/cover.webp')} style={styles.image} resizeMode="cover" />
        <Text style={styles.text}>anchor</Text>
    </NestedScrollViewHeader>
</NestedScrollView>
```

## 接口说明

> [!TIP] "Platform" 列表示这些属性在原始第三方库中支持的平台。

> [!TIP] "如果“HarmonyOS 支持”列的值为“yes”，则表示 HarmonyOS 平台支持该属性；“no”则表示不支持；“partially”表示部分支持该属性的功能。该属性在不同平台上的使用方法相同，效果与 iOS 或 Android 平台一致。

| Name        | Description                                       | Type   | Required | Platform | HarmonyOS Support |
| ----------- | ------------------------------------------------- | ------ | -------- | -------- | ----------------- |
| stickyHeight| 标题高度的区域会固定在顶部                                      | number | NO       | All      | yes               |
| stickyHeaderBeginIndex | 这意味着从前几个子组件开始，子组件将固定在顶部 | number | NO       | All      | yes               |
| bounce    | 弹性效果                               | boolean | NO       | All      | yes               |
| onScroll    |组件回调                             | function | NO       | All      | yes               |

## 遗留问题
无

## 目录结构

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

## 贡献代码

使用过程中发现任何问题都可以提交 [Issue](https://gitcode.com/CPF-RN/rntpc_react-native-nested-scroll/issues)，当然，也非常欢迎提交 [PR](https://github.com/react-native-oh-library/react-native-nested-scroll/pulls) 。

## 开源协议

本项目基于 [The MIT License (MIT)](https://github.com/sdcxtech/react-native-troika/blob/master/packages/nested-scroll/LICENSE)，请自由地享受和参与开源。

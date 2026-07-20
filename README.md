> 模板版本：v0.4.0

<p align="center">
  <h1 align="center"> <code>react-native-nested-scroll</code> </h1>
</p>

本项目基于 [react-native-nested-scroll@0.14.0](https://github.com/sdcxtech/react-native-troika/tree/master/packages/nested-scroll) 开发。


| 三方库名称                                           | 三方库版本            | 发布信息                                                                        | 支持RN版本          | Autolink | 编译API版本 | 社区基线版本 | npm地址                                                                                      |
| ----------------------------------------------- | ---------------- | --------------------------------------------------------------------------- | --------------- | -------- | ------- | ------ | ------------------------------------------------------------------------------------------ |
| @react-native-oh-tpl/react-native-nested-scroll | ~0.14.2  | [Github Releases](https://github.com/react-native-oh-library/react-native-nested-scroll/releases) | 0.72  | 否 | API12+ | 0.14.0 | [Npm Address](https://www.npmjs.com/package/@react-native-oh-tpl/react-native-nested-scroll) |

## 1. 安装与使用

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

下面的代码展示了这个库的基本使用场景：

> [!WARNING] 使用时 import 的库名不变。

```js
import {StyleSheet, View} from 'react-native';
import {NestedScrollView} from '@react-native-oh-tpl/react-native-nested-scroll';

import {FlatListPage} from './FlatListPage';
import {ParallaxHeader} from './ParallaxHeader';
import {useAnimateScrollView} from './hooks/useAnimatedScrollView';
import AnimatedNavbar from './AnimatedNavbar';
import {TopNavBar} from './components/TopNavBar';
import {HeaderNavBar} from './components/HeaderNavBar';
import {HeaderComponent} from './components/HeaderComponent';

// Within your render function
function NestedScrollParallaxHeader() {
    const imageHeight = 220;
    const [scroll, onScroll, scale, translateYDown, translateYUp] = useAnimateScrollView(
        imageHeight,
        false,
    );

    return (
      <View style={styles.fill}>
        <NestedScrollView bounces>
            <ParallaxHeader
                topBarHeight={180}
                imageHeight={180}
                imageSource={require('../assets/cover.webp')}
                scale={scale}
                translateYDown={translateYDown}
                translateYUp={translateYUp}>
                <HeaderComponent />
            </ParallaxHeader>
            <FlatListPage />
        </NestedScrollView>

        <AnimatedNavbar
            scroll={scroll}
            headerHeight={50}//topBarHeight()}
            statusBarHeight={80}//statusBarHeight()}
            imageHeight={imageHeight}
            OverflowHeaderComponent={<HeaderNavBar />}
            TopNavbarComponent={<TopNavBar />}
            /> 
      </View>
  );
}
export default NestedScrollParallaxHeader;
// Later on in your styles..
const styles = StyleSheet.create({
    fill: {
        flex: 1,
    },
    image: {
        height: 160,
        width: '100%',
    },
});
```

## 2. 约束与限制

### 2.1 兼容性

请到三方库相应的 Releases 发布地址查看 Release 配套的版本信息：[@react-native-oh-tpl/react-native-nested-scroll Releases](https://github.com/react-native-oh-library/react-native-nested-scroll/releases)

## 3. 属性

> [!TIP] "Platform" 列表示这些属性在原始第三方库中支持的平台。

> [!TIP] "如果“HarmonyOS 支持”列的值为“yes”，则表示 HarmonyOS 平台支持该属性；“no”则表示不支持；“partially”表示部分支持该属性的功能。该属性在不同平台上的使用方法相同，效果与 iOS 或 Android 平台一致。

| Name        | Description                                       | Type   | Required | Platform | HarmonyOS Support |
| ----------- | ------------------------------------------------- | ------ | -------- | -------- | ----------------- |
| stickyHeight| 标题高度的区域会固定在顶部                                      | number | NO       | All      | yes               |
| stickyHeaderBeginIndex | 这意味着从前几个子组件开始，子组件将固定在顶部 | number | NO       | All      | yes               |
| bounce    | 弹性效果                               | boolean | NO       | All      | yes               |
| onScroll    |组件回调                             | function | NO       | All      | yes               |

## 4. 遗留问题
无

## 5. 开源协议

本项目基于 [The MIT License (MIT)](https://github.com/sdcxtech/react-native-troika/blob/master/packages/nested-scroll/LICENSE)，请自由地享受和参与开源。

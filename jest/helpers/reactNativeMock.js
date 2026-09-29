/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * react-native 模块 mock：仅提供源码运行时真正用到的 API（StyleSheet.create），
 * 其余导入在 TypeScript 类型剥离后已被移除，不会真正执行 require('react-native')。
 */

module.exports = function reactNativeMockFactory() {
  return {
    StyleSheet: {
      create: (styles) => styles,
      flatten: (style) => (Array.isArray(style) ? style.filter(Boolean) : style),
    },
    requireNativeComponent: jest.fn(() => function MockNativeView() {
      return null;
    }),
    NativeModules: {},
    Platform: {
      OS: 'ohos',
      select: (options) =>
        options && options.ohos !== undefined ? options.ohos : options && options.default,
    },
  };
};

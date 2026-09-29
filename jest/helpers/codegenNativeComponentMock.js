/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * react-native/Libraries/Utilities/codegenNativeComponent 模块 mock：
 * 按组件名缓存并返回可渲染的 forwardRef 组件，宿主元素名即 codegen 注册名，
 * 便于测试中通过 findByType('<注册名>') 定位原生组件并断言其 props。
 */

module.exports = function codegenNativeComponentMockFactory() {
  const React = require('react');
  const registry = {};
  const codegenNativeComponent = jest.fn((name) => {
    if (!registry[name]) {
      const hostTag = String(name);
      registry[name] = React.forwardRef(function MockNativeComponent(props, ref) {
        return React.createElement(hostTag, { ...props, ref });
      });
    }
    return registry[name];
  });
  return { __esModule: true, default: codegenNativeComponent };
};

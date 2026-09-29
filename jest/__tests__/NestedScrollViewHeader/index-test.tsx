/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

jest.mock('react-native', () => require('../../helpers/reactNativeMock')());

jest.mock('react-native/Libraries/Utilities/codegenNativeComponent', () =>
  require('../../helpers/codegenNativeComponentMock')()
);

import React from 'react';
import { create } from 'react-test-renderer';
import { NestedScrollViewHeader } from '../../../src/NestedScrollViewHeader';
import NestedScrollViewHeaderNative from '../../../src/NestedScrollViewHeader/nestedScrollHeaderNativeComponent';

describe('NestedScrollViewHeader', () => {
  it('renders the codegen component which renders the RNCNestedScrollViewHeaderNative host', () => {
    const renderer = create(<NestedScrollViewHeader />);
    // 渲染链：forwardRef 包装组件 → codegen 产物组件 → 宿主元素
    expect(renderer.root.findByType(NestedScrollViewHeaderNative)).toBeDefined();
    expect(
      renderer.root.findByType('RNCNestedScrollViewHeaderNative')
    ).toBeDefined();
    renderer.unmount();
  });

  it('forwards all props to the native component', () => {
    const onScroll = jest.fn();
    const renderer = create(
      <NestedScrollViewHeader
        stickyHeight={10}
        stickyHeaderBeginIndex={2}
        onScroll={onScroll}
      />
    );
    const native = renderer.root.findByType('RNCNestedScrollViewHeaderNative');
    expect(native.props.stickyHeight).toBe(10);
    expect(native.props.stickyHeaderBeginIndex).toBe(2);
    expect(native.props.onScroll).toBe(onScroll);
    renderer.unmount();
  });

  it('renders children inside the native component', () => {
    const renderer = create(
      <NestedScrollViewHeader>
        <header>title</header>
      </NestedScrollViewHeader>
    );
    expect(renderer.root.findByType('header').props.children).toBe('title');
    renderer.unmount();
  });

  it('forwards the ref to the native component and detaches it on unmount', () => {
    // react-test-renderer 不创建真实节点，宿主元素 ref 需通过 createNodeMock 提供实例
    const hostInstance = { mockHostInstance: true };
    const ref = React.createRef();
    const renderer = create(<NestedScrollViewHeader ref={ref} />, {
      createNodeMock: () => hostInstance,
    });
    expect(ref.current).toBe(hostInstance);
    renderer.unmount();
    expect(ref.current).toBeNull();
  });
});

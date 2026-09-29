/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

jest.mock('react-native', () => require('../helpers/reactNativeMock')());

jest.mock('react-native/Libraries/Utilities/codegenNativeComponent', () =>
  require('../helpers/codegenNativeComponentMock')()
);

import React from 'react';
import { create } from 'react-test-renderer';
import { NestedScrollView, NestedScrollViewHeader } from '../../src/index';

describe('NestedScrollView', () => {
  it('renders the RNCNestedScrollView native component', () => {
    const renderer = create(<NestedScrollView />);
    expect(renderer.root.findByType('RNCNestedScrollView')).toBeDefined();
    renderer.unmount();
  });

  it('renders children inside the native component', () => {
    const renderer = create(
      <NestedScrollView>
        <view>child</view>
      </NestedScrollView>
    );
    const native = renderer.root.findByType('RNCNestedScrollView');
    expect(native.children).toHaveLength(1);
    expect(renderer.root.findByType('view').props.children).toBe('child');
    renderer.unmount();
  });

  it('merges the default fill style (flex: 1) before the custom style', () => {
    const customStyle = { height: 100 };
    const renderer = create(<NestedScrollView style={customStyle} />);
    const style = renderer.root.findByType('RNCNestedScrollView').props.style;
    expect(style).toHaveLength(2);
    expect(style[0]).toEqual({ flex: 1 });
    expect(style[1]).toBe(customStyle);
    renderer.unmount();
  });

  it('keeps the default fill style when no style is provided', () => {
    const renderer = create(<NestedScrollView />);
    const style = renderer.root.findByType('RNCNestedScrollView').props.style;
    expect(style).toHaveLength(2);
    expect(style[0]).toEqual({ flex: 1 });
    expect(style[1]).toBeUndefined();
    renderer.unmount();
  });

  it('forwards the remaining props to the native component', () => {
    const onScroll = jest.fn();
    const renderer = create(<NestedScrollView bounces={false} onScroll={onScroll} />);
    const native = renderer.root.findByType('RNCNestedScrollView');
    expect(native.props.bounces).toBe(false);
    expect(native.props.onScroll).toBe(onScroll);
    renderer.unmount();
  });

  it('does not forward the consumed style prop through the rest props twice', () => {
    // style 在包装组件中被单独展开为 [styles.fill, style]，不会再进入 {...props}
    const renderer = create(<NestedScrollView style={{ height: 10 }} />);
    const native = renderer.root.findByType('RNCNestedScrollView');
    expect(native.props.style).toHaveLength(2);
    renderer.unmount();
  });
});

describe('index module exports', () => {
  it('re-exports NestedScrollViewHeader which renders RNCNestedScrollViewHeaderNative', () => {
    expect(NestedScrollViewHeader).toBeDefined();
    const renderer = create(<NestedScrollViewHeader />);
    expect(
      renderer.root.findByType('RNCNestedScrollViewHeaderNative')
    ).toBeDefined();
    renderer.unmount();
  });
});

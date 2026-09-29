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
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';
import NestedScrollViewHeaderNative from '../../../src/NestedScrollViewHeader/nestedScrollHeaderNativeComponent';

const codegenMock = codegenNativeComponent as jest.Mock;

describe('nestedScrollHeaderNativeComponent', () => {
  it('registers RNCNestedScrollViewHeaderNative via codegenNativeComponent at module load', () => {
    expect(codegenMock).toHaveBeenCalledTimes(1);
    expect(codegenMock).toHaveBeenCalledWith('RNCNestedScrollViewHeaderNative');
  });

  it('default export is the component created by codegenNativeComponent', () => {
    expect(NestedScrollViewHeaderNative).toBe(codegenMock.mock.results[0].value);
  });

  it('default export is renderable as the RNCNestedScrollViewHeaderNative host component', () => {
    const renderer = create(<NestedScrollViewHeaderNative />);
    expect(
      renderer.root.findByType('RNCNestedScrollViewHeaderNative')
    ).toBeDefined();
    renderer.unmount();
  });
});

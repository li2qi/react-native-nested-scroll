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
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';
import NestedScrollViewNativeComponent from '../../src/nestedScrollNativeComponent';

const codegenMock = codegenNativeComponent as jest.Mock;

describe('nestedScrollNativeComponent', () => {
  it('registers RNCNestedScrollView via codegenNativeComponent at module load', () => {
    expect(codegenMock).toHaveBeenCalledTimes(1);
    expect(codegenMock).toHaveBeenCalledWith('RNCNestedScrollView');
  });

  it('default export is the component created by codegenNativeComponent', () => {
    expect(NestedScrollViewNativeComponent).toBe(codegenMock.mock.results[0].value);
  });

  it('default export is renderable as the RNCNestedScrollView host component', () => {
    const renderer = create(<NestedScrollViewNativeComponent />);
    expect(renderer.root.findByType('RNCNestedScrollView')).toBeDefined();
    renderer.unmount();
  });
});

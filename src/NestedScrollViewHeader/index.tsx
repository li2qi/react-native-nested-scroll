import React from 'react'
import { NativeScrollPoint, NativeSyntheticEvent, requireNativeComponent, ViewProps } from 'react-native'

import NestedScrollViewHeaderNative from './nestedScrollHeaderNativeComponent'
import {NestedScrollViewHeaderProps} from './nestedScrollHeaderNativeComponent'


const NativeNestedScrollViewHeader = NestedScrollViewHeaderNative
// const NativeNestedScrollViewHeader = requireNativeComponent<NestedScrollViewHeaderProps>('NestedScrollViewHeader')

type NativeNestedScrollViewHeaderInstance = InstanceType<typeof NativeNestedScrollViewHeader>

const NestedScrollViewHeader = React.forwardRef<NativeNestedScrollViewHeaderInstance, NestedScrollViewHeaderProps>(
  (props, ref) => {
    return <NativeNestedScrollViewHeader {...props} ref={ref} />
  },
)

export { NestedScrollViewHeader }

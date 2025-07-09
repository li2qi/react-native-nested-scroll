import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent"
import {
    NativeSyntheticEvent,
    StyleProp,
    ViewStyle,
    NativeScrollPoint,
    HostComponent,
    ViewProps,
  } from 'react-native'

  import type {
    WithDefault,
    DirectEventHandler,
    Int32,
  } from 'react-native/Libraries/Types/CodegenTypes';

  export type NestedScrollEvent = Readonly<{
    x: Int32;
    y: Int32;
  }>

  export interface NestedScrollViewHeaderProps extends ViewProps {
    stickyHeight?: WithDefault<Int32, -1>;
    stickyHeaderBeginIndex?: WithDefault<Int32, -1>;
    onScroll?: DirectEventHandler<NestedScrollEvent>;
  }
  
export default codegenNativeComponent<NestedScrollViewHeaderProps>("RNCNestedScrollViewHeaderNative") as HostComponent<NestedScrollViewHeaderProps>; 

import {
    HostComponent,
    ViewProps,
} from "react-native";

import codegenNativeComponent from "react-native/Libraries/Utilities/codegenNativeComponent"
import { Int32, DirectEventHandler, WithDefault } from "react-native/Libraries/Types/CodegenTypes";

export type NestedScrollEvent = Readonly<{
    ContentInset: {
        left: Int32;
        top: Int32;
        bottom: Int32;
        right: Int32;
    };
    ContentOffset: {
        x: Int32;
        y: Int32;
    };
    ContentSize: {
        height: Int32;
        width: Int32;
    };
    LayoutMeasurement: {
        height: Int32;
        width: Int32;
    };
    lTargetContentOffset: {
        x: Int32;
        y: Int32;
    };
    zoomScale: Int32;
}>

export interface NestScrollProps extends ViewProps {
    bounces?: WithDefault<boolean, false>;
    onScroll?: DirectEventHandler<NestedScrollEvent>;
}

export default codegenNativeComponent<NestScrollProps>("RNCNestedScrollView") as HostComponent<NestScrollProps>; 

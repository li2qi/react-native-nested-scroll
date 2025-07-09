import React from 'react'
import NestedScrollViewNativeComponent from './nestedScrollNativeComponent'
import {NestScrollProps as NestedScrollViewProps} from "./nestedScrollNativeComponent"
import {
  StyleSheet,
} from 'react-native'

const NestedScrollViewNative = NestedScrollViewNativeComponent;

function NestedScrollView({ children, style, ...props }: NestedScrollViewProps) {      
  return (
    <NestedScrollViewNative style={[styles.fill, style]} {...props} >
      {children}
    </NestedScrollViewNative>
  )
}

const styles = StyleSheet.create({
  fill: {
    flex: 1,
  },
  content: {
    flex: 1,
  },
})

export { NestedScrollView }

export { NestedScrollViewHeader } from './NestedScrollViewHeader'

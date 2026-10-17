import {useCallback, useMemo, useRef, useState} from 'react';
import {Animated, Platform} from 'react-native';
import type {
  default as PagerView,
  PagerViewOnPageScrollEventData,
  PagerViewOnPageSelectedEvent,
  PageScrollStateChangedNativeEvent,
} from 'react-native-pager-view';

export default function usePagerView(initialPage = 0) {
  const pagerRef = useRef<PagerView>(null); // 引用 PagerView 组件
  const [activePage, setActivePage] = useState(initialPage); // 当前活跃页面的索引
  const [isIdle, setIdle] = useState(true); // 是否处于空闲状态（可能用于防抖/节流）
  const setPage = useCallback((page: number, animated = true) => {
    if (animated) {
      pagerRef.current?.setPage(page);
    } else {
      pagerRef.current?.setPageWithoutAnimation(page);
    }
    setActivePage(page);
  }, []);
  const offset = useRef(new Animated.Value(0)).current;
  const position = useRef(new Animated.Value(0)).current;
  const onPageScroll = useMemo(
    () =>
      Animated.event<PagerViewOnPageScrollEventData>(
        [
          {
            nativeEvent: {
              offset: offset,
              position: position,
            },
          },
        ],
        {
          useNativeDriver: true,
        },
      ),
    [offset, position],
  );
  const onPageSelected = useCallback((e: PagerViewOnPageSelectedEvent) => {
    setActivePage(e.nativeEvent.position);
  }, []);
  const onPageScrollStateChanged = useCallback(
    ({nativeEvent: {pageScrollState}}: PageScrollStateChangedNativeEvent) => {},
    [],
  );
  return {
    pagerRef,
    setPage,
    page: activePage,
    isIdle,
    position,
    offset,
    onPageScroll,
    onPageSelected,
    onPageScrollStateChanged,
  };
}

function time() {
  const date = new Date();
  return (
    date.getHours() +
    '时' +
    date.getMinutes() +
    '分' +
    date.getSeconds() +
    '秒:' +
    date.getMilliseconds()
  );
}

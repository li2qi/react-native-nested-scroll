import React from 'react';
import NestedScrollFlatList from './NestedScrollFlatList';
import NestedScrollStickyHeightBeginIndex from './NestedScrollFlatList/nestedScrollStickyHeightBeginIndex';
import NestedScrollTabView from './NestedScrollTabView';
import NestedScrollParallaxHeader from './NestedScrollParallaxHeader';
import NestedScrollPagerViewStickyHeader from './NestedScrollPagerViewStickyHeader';
import NestedScrollPointerEvents from './NestedScrollPointerEvents';

export interface SceneItem {
  key: string;
  title: string;
  description: string;
  props: string[];
  component: React.ComponentType<object>;
}

export const SCENES: SceneItem[] = [
  {
    key: 'flat_list',
    title: 'NestedScrollFlatList',
    description: 'NestedScrollView + NestedScrollViewHeader (stickyHeight) + FlatList',
    props: ['stickyHeight', 'bounces', 'FlatList'],
    component: NestedScrollFlatList,
  },
  {
    key: 'sticky_height_begin_index',
    title: 'nestedScrollStickyHeightBeginIndex',
    description: 'NestedScrollViewHeader stickyHeaderBeginIndex=2, sticky anchors inside header',
    props: ['stickyHeaderBeginIndex', 'bounces', 'FlatList', 'ScrollView'],
    component: NestedScrollStickyHeightBeginIndex,
  },
  {
    key: 'tab_view',
    title: 'NestedScrollTabView',
    description: 'NestedScrollView + header + tab view (Article/Albums/Contacts/Chat), dynamic header height',
    props: ['stickyHeaderBeginIndex', 'onScroll', 'Button', 'TabView'],
    component: NestedScrollTabView,
  },
  {
    key: 'parallax_header',
    title: 'NestedScrollParallaxHeader',
    description: 'Parallax header with scale/translate animations + FlatList page + animated navbar',
    props: ['bounces', 'Animated', 'FlatList', 'ParallaxHeader'],
    component: NestedScrollParallaxHeader,
  },
  {
    key: 'pager_sticky_header',
    title: 'NestedScrollPagerViewStickyHeader',
    description: 'Sticky header (stickyHeaderBeginIndex=1) + pager pages: SectionList / FlatList / ScrollView',
    props: ['stickyHeaderBeginIndex', 'bounces', 'PagerView', 'TabBar'],
    component: NestedScrollPagerViewStickyHeader,
  },
  {
    key: 'pointer_events',
    title: 'NestedScrollPointerEvents',
    description: 'pointerEvents modes (auto/none/box-only/box-none) on header and scroll content',
    props: ['pointerEvents', 'bounces', 'ScrollView'],
    component: NestedScrollPointerEvents,
  },
];

export default SCENES;

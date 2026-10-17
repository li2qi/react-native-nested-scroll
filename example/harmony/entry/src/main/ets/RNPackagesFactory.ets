/*
 * Copyright (c) 2025 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */


import type {RNPackageContext, RNPackage} from '@rnoh/react-native-openharmony/ts';
import { ViewPagerPackage } from '@react-native-ohos/react-native-pager-view/ts';

export function createRNPackages(ctx: RNPackageContext): RNPackage[] {
  return [
    new ViewPagerPackage(ctx)
  ];
}

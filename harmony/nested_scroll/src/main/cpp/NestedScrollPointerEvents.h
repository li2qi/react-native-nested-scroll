/**
 * MIT License
 *
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HARMONY_NESTED_SCROLL_POINTER_EVENTS_H
#define HARMONY_NESTED_SCROLL_POINTER_EVENTS_H

#include "RNOH/arkui/ArkUINode.h"
#include <react/renderer/components/view/primitives.h>

namespace rnoh {

/**
 * RN pointerEvents -> ArkUI hitTestBehavior on the scroll container.
 *
 * CppComponentInstance's touch intercept already gates children and JS touch
 * dispatch, but the container itself (including its built-in scroll gesture)
 * stays a touch target. HitTestMode NONE skips only the node itself in hit
 * testing, so None/BoxNone disable the container while children keep the
 * intercept-based gating.
 */
inline void setNestedScrollPointerEvents(
    ArkUINode &node, facebook::react::PointerEventsMode pointerEvents) {
  auto hitTestMode =
      (pointerEvents == facebook::react::PointerEventsMode::Auto ||
       pointerEvents == facebook::react::PointerEventsMode::BoxOnly)
      ? ARKUI_HIT_TEST_MODE_DEFAULT
      : ARKUI_HIT_TEST_MODE_NONE;
  node.setHitTestMode(hitTestMode);
}

} // namespace rnoh

#endif // HARMONY_NESTED_SCROLL_POINTER_EVENTS_H

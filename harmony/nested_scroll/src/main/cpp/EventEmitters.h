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

#ifndef EVENT_EMITTERS_H  // 如果没有定义 EVENT_EMITTERS_H，则编译以下内容
#define EVENT_EMITTERS_H

#include <cstdint>
#include <react/renderer/components/view/ViewEventEmitter.h>
#include <jsi/jsi.h>

namespace facebook {
    namespace react {

        class JSI_EXPORT NestedScrollViewHeaderEventEmitter : public ViewEventEmitter {
        public:
            using ViewEventEmitter::ViewEventEmitter;
            struct NestedScrollHeaderEvent {
                Float x;
                Float y;
            };
            void onScroll(NestedScrollHeaderEvent value) const;
        };

        class JSI_EXPORT NestedScrollViewEventEmitter : public ViewEventEmitter {
        public:
            using ViewEventEmitter::ViewEventEmitter;

            struct ContentInset {
                Float left;
                Float top;
                Float bottom;
                Float right;
            };

            struct ContentOffset {
                float x;
                float y;
            };

            struct ContentSize {
                Float height;
                Float width;
            };

            struct LayoutMeasurement {
                Float height;
                Float width;
            };
            struct TargetContentOffset {
                int x;
                int y;
            };

            struct NestedScrollEvent {
                Float zoomScale;
                ContentInset contentInset;
                ContentOffset contentOffset;
                ContentSize contentSize;
                LayoutMeasurement layoutMeasurement;
                TargetContentOffset targetContentOffset;
            };
            void onScroll(NestedScrollEvent value) const;
        };
       

    } // namespace react
} // namespace facebook
#endif  // 结束条件编译
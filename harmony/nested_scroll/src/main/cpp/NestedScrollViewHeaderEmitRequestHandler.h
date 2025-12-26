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

#ifndef HARMONY_NESTED_SCROLL_SRC_MAIN_CPP_HEADEREMITREQUESTHANDLER_H
#define HARMONY_NESTED_SCROLL_SRC_MAIN_CPP_HEADEREMITREQUESTHANDLER_H

#include "glog/logging.h"
#include "EventEmitters.h"
#include "RNOH/ArkJS.h"
#include "RNOH/EventEmitRequestHandler.h"

namespace rnoh {

    class NestedScrollViewHeaderEmitRequestHandler : public EventEmitRequestHandler {
    public:
        void handleEvent(EventEmitRequestHandler::Context const &ctx) override {
            ArkJS arkJs(ctx.env);
            auto eventName = ctx.eventName;
            auto eventEmitter =
                ctx.shadowViewRegistry->getEventEmitter<facebook::react::NestedScrollViewHeaderEventEmitter>(ctx.tag);
            if (eventEmitter == nullptr) {
                return;
            }
          if (eventName == "onScroll") {
                float contentOffsetX = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "x"));
                float contentOffsetY = (float)arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "y"));
                facebook::react::NestedScrollViewHeaderEventEmitter::NestedScrollHeaderEvent nestedScrollHeaderEvent{contentOffsetX, contentOffsetY};
                eventEmitter->onScroll(nestedScrollHeaderEvent);
            } 
        }
    };

} // namespace rnoh
#endif
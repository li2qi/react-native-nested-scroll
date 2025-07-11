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

#include "NestedScrollViewComponentInstance.h"
#include "NestedScrollViewHeaderComponentInstance.h"
#include <glog/logging.h>
#include "RNOH/ArkTSBridge.h"

namespace rnoh {
NestedScrollViewHeaderComponentInstance::NestedScrollViewHeaderComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
}

void NestedScrollViewHeaderComponentInstance::onFinalizeUpdates() {
    ComponentInstance::onFinalizeUpdates();
}

void NestedScrollViewHeaderComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                        std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
    auto item = NativeNodeApi::getInstance()->getAttribute(
    childComponentInstance->getLocalRootArkUINode().getArkUINodeHandle(), NODE_HEIGHT);
    if (stickyHeight >= 0 || stickyHeaderBeginIndex >= 0) {
        if (stickyHeight >= 0) {//stickyHeight 优先级 高于 stickyHeaderBeginIndex
            stickyHeaderHeight = stickyHeight;
            mNestedScrollHeaderNode.insertChild(childComponentInstance->getLocalRootArkUINode(),index);
        } else if (stickyHeaderBeginIndex >= 0) {
            if(beginIndex >= stickyHeaderBeginIndex) {
                stickyHeaderHeight += childComponentInstance->getLayoutMetrics().frame.size.height;
            }
            mNestedScrollHeaderNode.insertChild(childComponentInstance->getLocalRootArkUINode(),index);
            beginIndex++;
        }
    } else {
        mNestedScrollHeaderNode.insertChild(childComponentInstance->getLocalRootArkUINode(),index);
    }
}

void NestedScrollViewHeaderComponentInstance::onScroll(facebook::react::NestedScrollViewHeaderEventEmitter::NestedScrollHeaderEvent nestedScrollHeaderEvent) {
    m_eventEmitter->onScroll(nestedScrollHeaderEvent);
}   

void NestedScrollViewHeaderComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
    CppComponentInstance::onChildRemoved(childComponentInstance);
    mNestedScrollHeaderNode.removeChild(childComponentInstance->getLocalRootArkUINode());
};

NestedScrollViewHeaderNode &NestedScrollViewHeaderComponentInstance::getLocalRootArkUINode() { return mNestedScrollHeaderNode; }

void NestedScrollViewHeaderComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    if (auto p = std::dynamic_pointer_cast<const facebook::react::RNCNestedScrollViewHeaderProps>(props)) {
        stickyHeight =  p->stickyHeight;
        stickyHeaderBeginIndex = p->stickyHeaderBeginIndex;
    }
}

void NestedScrollViewHeaderComponentInstance::onLayoutChanged(
    facebook::react::LayoutMetrics const& layoutMetrics) {
        float width = layoutMetrics.frame.size.width;
        float height = layoutMetrics.frame.size.height;
        mNestedScrollHeaderNode.setWidth(width);
        mNestedScrollHeaderNode.setHeight(height);
    }
} // namespace rnoh
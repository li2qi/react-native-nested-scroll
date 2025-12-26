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

#include "NestedScrollViewHeaderComponentInstance.h"
#include "NestedScrollViewComponentInstance.h"
#include <regex>
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

NestedScrollViewComponentInstance::NestedScrollViewComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
    mNestedScrollNode.setScrollNodeDelegate(this);
    mNestedScrollNode.setAlignment(ARKUI_ALIGNMENT_TOP);
}

facebook::react::Point NestedScrollViewComponentInstance::getCurrentOffset() const {
  auto offset = mNestedScrollNode.getScrollOffset();
  return offset;
}

void NestedScrollViewComponentInstance::onFinalizeUpdates() {
  ComponentInstance::onFinalizeUpdates();
    float scrollHeight = 0.0f;
    headerHeight = this->getLocalRootArkUINode().getHeaderChild()->getLayoutMetrics().frame.size.height;
    if (rNCNestedScrollViewHeaderNative != nullptr) {
        scrollHeight = headerHeight - rNCNestedScrollViewHeaderNative->stickyHeaderHeight;
    }
    fixColumnAll.setHeight(layoutMetricsHeight + scrollHeight);
    mNestedScrollNode.insertChild(fixColumnAll, 0);
}

void NestedScrollViewComponentInstance::onChildInserted(
    ComponentInstance::Shared const& childComponentInstance, std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
    if (childComponentInstance->getComponentName() == "RNCNestedScrollViewHeaderNative") {
        elementPositionRelativeFixHeader = true;//记录元素在固定的头部还是尾部
        rNCNestedScrollViewHeaderNative = std::dynamic_pointer_cast<NestedScrollViewHeaderComponentInstance>(childComponentInstance);
        this->getLocalRootArkUINode().setHeaderChild(childComponentInstance);
        fixColumnAll.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    } else {
        this->getLocalRootArkUINode().setChild(childComponentInstance);
        fixColumnAll.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }
}

void NestedScrollViewComponentInstance::onLayoutChanged(
    const facebook::react::LayoutMetrics& layoutMetrics) {
    CppComponentInstance::onLayoutChanged(layoutMetrics);
    layoutMetricsHeight = layoutMetrics.frame.size.height;
}
void NestedScrollViewComponentInstance::onChildRemoved(
    ComponentInstance::Shared const& childComponentInstance) {
  CppComponentInstance::onChildRemoved(childComponentInstance);
  mNestedScrollNode.removeChild(
      childComponentInstance->getLocalRootArkUINode());
}

NestedScrollViewNode &NestedScrollViewComponentInstance::getLocalRootArkUINode() { return mNestedScrollNode; }

void NestedScrollViewComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    bounces = props->bounces;
    this->getLocalRootArkUINode().setScrollBarOff(mNestedScrollNode.getArkUINodeHandle());

}

void NestedScrollViewComponentInstance::onScroll(facebook::react::NestedScrollViewEventEmitter::NestedScrollEvent nestedScrollEvent) {
    auto item = NativeNodeApi::getInstance()->getAttribute(mNestedScrollNode.getArkUINodeHandle(), NODE_SCROLL_OFFSET);
    facebook::react::NestedScrollViewHeaderEventEmitter::NestedScrollHeaderEvent nestedScrollHeaderEvent{
                item->value[0].f32,
                item->value[1].f32
            };
    rNCNestedScrollViewHeaderNative->onScroll(nestedScrollHeaderEvent);
}

} // namespace rnoh

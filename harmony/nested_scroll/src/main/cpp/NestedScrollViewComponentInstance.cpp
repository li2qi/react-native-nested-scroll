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
    NativeNodeApi::getInstance()->registerNodeEvent(mNestedScrollNode.getArkUINodeHandle(), NODE_SCROLL_EVENT_ON_SCROLL,
                                                        NODE_SCROLL_EVENT_ON_SCROLL, this);
}

void NestedScrollViewComponentInstance::onFinalizeUpdates() {
  ComponentInstance::onFinalizeUpdates();
    mNestedScrollNode.insertChild(fixColumnAll, 0);
    mNestedScrollNode.setAlignment(ARKUI_ALIGNMENT_TOP);
}

void NestedScrollViewComponentInstance::onChildInserted(
    ComponentInstance::Shared const& childComponentInstance, std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
    if (childComponentInstance->getComponentName() == "RNCNestedScrollViewHeaderNative") {
        elementPositionRelativeFixHeader = true;//记录元素在固定的头部还是尾部
        rNCNestedScrollViewHeaderNative = std::dynamic_pointer_cast<NestedScrollViewHeaderComponentInstance>(childComponentInstance);
        float scrollHeight = childComponentInstance->getLayoutMetrics().frame.size.height - 
            rNCNestedScrollViewHeaderNative->stickyHeaderHeight;
        fixColumnAll.setHeight(m_layoutMetrics.frame.size.height + scrollHeight);
        fixColumnAll.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    } else {
        handleScrollView(childComponentInstance);
        childComponentInstance->getLocalRootArkUINode().setHeight(m_layoutMetrics.frame.size.height - rNCNestedScrollViewHeaderNative->stickyHeaderHeight);
        fixColumnAll.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }
}

void NestedScrollViewComponentInstance::handleScrollView(ComponentInstance::Shared childComponentInstance){
     if (OH_ArkUI_NodeUtils_GetNodeType(childComponentInstance->getLocalRootArkUINode().getArkUINodeHandle()) == 
         ARKUI_NODE_SCROLL ) {
        this->getLocalRootArkUINode().setScrollBarOff(childComponentInstance->getLocalRootArkUINode().getArkUINodeHandle());
        this->getLocalRootArkUINode().setBounce(childComponentInstance->getLocalRootArkUINode().getArkUINodeHandle(), bounces);
        this->getLocalRootArkUINode().setNestedScrollMode(childComponentInstance);
    } else {
        std::vector<ComponentInstance::Shared> children = childComponentInstance->getChildren();
        for (int childrenIndex = 0; childrenIndex < children.size(); childrenIndex++) {
            handleScrollView(children[childrenIndex]);
        }
    }
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

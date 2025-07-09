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

#include "RNOH/arkui/NativeNodeApi.h"
#include "NestedScrollViewNode.h"
#include "RNOHCorePackage/ComponentInstances/ScrollViewComponentInstance.h"

namespace rnoh {
NestedScrollViewNode::NestedScrollViewNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_SCROLL)) {
    NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, NODE_SCROLL_EVENT_ON_SCROLL,
                                                        NODE_SCROLL_EVENT_ON_SCROLL, this);
}

NestedScrollViewNode::~NestedScrollViewNode() {
}

void NestedScrollViewNode::insertChild(ArkUINode &child, std::size_t index) {
    maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(), index));
}

void NestedScrollViewNode::removeChild(ArkUINode &child) {
    maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
}

void NestedScrollViewNode::setBounce(ArkUI_NodeHandle node, bool bounces) {
    ArkUI_NumberValue nestedScrollValue[] ={{.i32 = !bounces}};
    ArkUI_AttributeItem nestedScrollItem = {nestedScrollValue, sizeof(nestedScrollValue) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(node, NODE_SCROLL_EDGE_EFFECT, &nestedScrollItem));
}
 
void NestedScrollViewNode::setNestedScrollMode(ComponentInstance::Shared childComponentInstance) {
    ArkUI_NumberValue scrollNestedValue[] ={{.i32 = ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST},{.i32 = ARKUI_SCROLL_NESTED_MODE_SELF_FIRST}};
    ArkUI_AttributeItem nestedScrollItem = {scrollNestedValue, sizeof(scrollNestedValue) / sizeof(ArkUI_NumberValue)};
    auto scrollView = std::dynamic_pointer_cast<ScrollViewComponentInstance>(childComponentInstance);
    scrollView->setNestedScrollMode(ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST, ARKUI_SCROLL_NESTED_MODE_SELF_FIRST);
//     maybeThrow(NativeNodeApi::getInstance()->setAttribute(scrollView->getLocalRootArkUINode().getArkUINodeHandle(), NODE_SCROLL_NESTED_SCROLL, &nestedScrollItem));
}

void NestedScrollViewNode::setScrollBarOff(ArkUI_NodeHandle node) {
    ArkUI_NumberValue alignValue[] ={{.i32 = ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF}};
    ArkUI_AttributeItem alignItem = {alignValue, sizeof(alignValue) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(node, NODE_SCROLL_BAR_DISPLAY_MODE, &alignItem));
}

void NestedScrollViewNode::setScrollNodeDelegate(NestedScrollNodeDelegate *scrollNodeDelegate) {
    m_scrollNodeDelegate = scrollNodeDelegate;
}

void NestedScrollViewNode::onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) {
        if (m_scrollNodeDelegate == nullptr)
            return;
        if (eventType == ArkUI_NodeEventType::NODE_SCROLL_EVENT_ON_SCROLL) {
            auto item = NativeNodeApi::getInstance()->getAttribute(m_nodeHandle, NODE_SCROLL_OFFSET);
            facebook::react::NestedScrollViewEventEmitter::NestedScrollEvent event = {
            };
            m_scrollNodeDelegate->onScroll(event);
        }
    }

} // namespace rnoh
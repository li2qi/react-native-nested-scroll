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
static void receiveEvent(ArkUI_NodeEvent* event) {
#ifdef C_API_ARCH
  try {
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    auto target = static_cast<NestedScrollViewNode*>(
        OH_ArkUI_NodeEvent_GetUserData(event));

    if (eventType == ArkUI_NodeEventType::NODE_TOUCH_EVENT) {
      target->handleScroll();
      return;
    }
  } catch (std::exception& e) {
    LOG(ERROR) << e.what();
  }
#endif
}

NestedScrollViewNode::NestedScrollViewNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_SCROLL)) {
    NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, NODE_SCROLL_EVENT_ON_SCROLL,
                                                        NODE_SCROLL_EVENT_ON_SCROLL, this);
    NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, NODE_TOUCH_EVENT,
                                                        NODE_SCROLL_EVENT_ON_SCROLL, this);
    maybeThrow(NativeNodeApi::getInstance()->addNodeEventReceiver(m_nodeHandle, receiveEvent));
}

NestedScrollViewNode::~NestedScrollViewNode() {
}

void NestedScrollViewNode::handleScroll() {
    if (child) {
        handleScrollView(child);
    }
}

void NestedScrollViewNode::setChild(ComponentInstance::Shared childComponentInstance) {
    child = childComponentInstance;
}

void NestedScrollViewNode::setHeaderChild(ComponentInstance::Shared childComponentInstance) {
    headerChild = childComponentInstance;
}
ComponentInstance::Shared NestedScrollViewNode::getHeaderChild(){
    return headerChild;
}

void NestedScrollViewNode::handleScrollView(ComponentInstance::Shared childComponentInstance){
     if (OH_ArkUI_NodeUtils_GetNodeType(childComponentInstance->getLocalRootArkUINode().getArkUINodeHandle()) == 
         ARKUI_NODE_SCROLL ) {
        setNestedScrollMode(childComponentInstance);
    } else {
        std::vector<ComponentInstance::Shared> children = childComponentInstance->getChildren();
        if (children.size() > 0) {
            for (int childrenIndex = 0; childrenIndex < children.size(); childrenIndex++) {
                handleScrollView(children[childrenIndex]);
            }
        }
    }
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

facebook::react::Point NestedScrollViewNode::getScrollOffset() const {
    auto item = NativeNodeApi::getInstance()->getAttribute(
      m_nodeHandle, NODE_SCROLL_OFFSET);
    facebook::react::Float x = item->value[0].f32;
    facebook::react::Float y = item->value[1].f32;
    return facebook::react::Point{x, y};
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
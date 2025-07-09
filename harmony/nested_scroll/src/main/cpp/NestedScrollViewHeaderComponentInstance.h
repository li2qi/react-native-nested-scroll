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

#pragma once

#ifndef HARMONY_NESTEDSCROLLVIEWHEADERCOMPONENTINSTANCE_H
#define HARMONY_NESTEDSCROLLVIEWHEADERCOMPONENTINSTANCE_H

#include "NestedScrollViewHeaderNode.h"
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"

namespace rnoh {
class NestedScrollViewComponentInstance;

class NestedScrollViewHeaderComponentInstance : public CppComponentInstance<facebook::react::RNCNestedScrollViewHeaderNode>{
private:
    NestedScrollViewHeaderNode mNestedScrollHeaderNode;
    facebook::react::Size m_containerSize;
    
public:
    
    float stickyHeight;
    float stickyHeaderHeight = 0.0f;
    int stickyHeaderBeginIndex;
    int beginIndex = 0;
    NestedScrollViewHeaderComponentInstance(Context context);
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
    void onFinalizeUpdates();
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    NestedScrollViewHeaderNode &getLocalRootArkUINode() override;
    void onPropsChanged(SharedConcreteProps const &props) override;
    void onScroll(facebook::react::NestedScrollViewHeaderEventEmitter::NestedScrollHeaderEvent nestedScrollHeaderEvent);
    void onLayoutChanged(facebook::react::LayoutMetrics const& layoutMetrics) override;
};
} // namespace rnoh

#endif // HARMONY_CLIPPATHVIEWCOMPONENTINSTANCE_H
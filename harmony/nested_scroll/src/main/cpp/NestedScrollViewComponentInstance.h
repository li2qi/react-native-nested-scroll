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

#ifndef HARMONY_NESTED_SCROLL_COMPONENTINSTANCE_H
#define HARMONY_NESTED_SCROLL_COMPONENTINSTANCE_H

#include "NestedScrollViewNode.h"
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "NestedScrollViewHeaderNode.h"

namespace rnoh {
class NestedScrollViewHeaderComponentInstance;
class NestedScrollViewComponentInstance : public CppComponentInstance<facebook::react::RNCNestedScrollNode>, public NestedScrollNodeDelegate{
private:
   
    std::shared_ptr<NestedScrollViewHeaderComponentInstance> rNCNestedScrollViewHeaderNative {nullptr};
    bool bounces;
    bool elementPositionRelativeFixHeader = false;

public:

    NestedScrollViewNode mNestedScrollNode;
    NestedScrollViewHeaderNode fixColumnAll;
    void onFinalizeUpdates();
    float headerHeight = 0;
    float layoutMetricsHeight = 0;
    NestedScrollViewComponentInstance(Context context);
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    NestedScrollViewNode &getLocalRootArkUINode() override;
    void onPropsChanged(SharedConcreteProps const &props) override;
    void onScroll(facebook::react::NestedScrollViewEventEmitter::NestedScrollEvent nestedScrollEvent) override;
    void onLayoutChanged(const facebook::react::LayoutMetrics& layoutMetrics) override;
    facebook::react::Point getCurrentOffset() const override;
};
} // namespace rnoh
#endif 
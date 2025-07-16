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

#ifndef HARMONY_NESTED_SCROLL_HEADER_SRC_MAIN_CPP_NESTEDSCROLLHEADERNONENAPIBINDER_H
#define HARMONY_NESTED_SCROLL_HEADER_SRC_MAIN_CPP_NESTEDSCROLLHEADERNONENAPIBINDER_H
#include "RNOHCorePackage/ComponentBinders/ViewComponentNapiBinder.h"
#include "Props.h"

namespace rnoh {

    class NestedScrollViewHeaderNapiBinder : public ViewComponentNapiBinder {
    public:
        napi_value createProps(napi_env env, facebook::react::ShadowView const shadowView) override {
            napi_value napiViewProps = ViewComponentNapiBinder::createProps(env, shadowView);
            auto propsObjBuilder = ArkJS(env).getObjectBuilder(napiViewProps);

            if (auto props = std::dynamic_pointer_cast<const facebook::react::RNCNestedScrollViewHeaderProps>(shadowView.props)) {
                propsObjBuilder.addProperty("stickyHeight", props->stickyHeight);
                propsObjBuilder.addProperty("stickyHeaderBeginIndex", props->stickyHeaderBeginIndex);
                auto boxArray = std::vector<napi_value>();
                auto boxArrayRaw = props->viewBox;
                for (auto item : boxArrayRaw) {
                    auto itemObjBuilder = ArkJS(env).createDouble(item);
                    boxArray.push_back(itemObjBuilder);
                }
                auto boxArrayArray = ArkJS(env).createArray(boxArray);
                propsObjBuilder.addProperty("viewBox", boxArrayArray);
                return propsObjBuilder.build();
            }
            return napiViewProps;
        };
    };

} // namespace rnoh
#endif
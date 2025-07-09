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

#ifndef HARMONY_CLIP_PATH_VIEW_SRC_MAIN_CPP_CLIPPATHVIEWPACKAGE_H
#define HARMONY_CLIP_PATH_VIEW_SRC_MAIN_CPP_CLIPPATHVIEWPACKAGE_H

#include "RNOH/Package.h"
#include "ComponentDescriptors.h"

#include "NestedScrollViewHeaderJSIBinder.h"
#include "NestedScrollViewHeaderNapiBinder.h"

#include "NestedScrollViewJSIBinder.h"
#include "NestedScrollViewNapiBinder.h"

#include "NestedScrollViewComponentInstance.h"
#include "NestedScrollViewHeaderComponentInstance.h"

#include "NestedScrollViewEmitRequestHandler.h"
#include "NestedScrollViewHeaderEmitRequestHandler.h"

namespace rnoh {
    class NestedScrollViewPackageComponentInstanceFactoryDelegate : public ComponentInstanceFactoryDelegate {
    public:
        using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;
        ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
            if (ctx.componentName == "RNCNestedScrollView") {
                return std::make_shared<NestedScrollViewComponentInstance>(std::move(ctx));
            } else if (ctx.componentName == "RNCNestedScrollViewHeaderNative") {
                return std::make_shared<NestedScrollViewHeaderComponentInstance>(std::move(ctx));
            }
            return nullptr;
        }
    };

    class NestedScrollViewPackage : public Package {
    public:
        NestedScrollViewPackage(Package::Context ctx) : Package(ctx) {}

        ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override {
            return std::make_shared<NestedScrollViewPackageComponentInstanceFactoryDelegate>();
        }

        std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override {
            return {
                facebook::react::concreteComponentDescriptorProvider<
                    facebook::react::RNCNestedScrollViewComponentDescriptor>(),
                facebook::react::concreteComponentDescriptorProvider<
                    facebook::react::RNCNestedScrollViewComponentHeaderDescriptor>(),};
        }

        ComponentJSIBinderByString createComponentJSIBinderByName() override {
            return {
                {"RNCNestedScrollView", std::make_shared<NestedScrollViewJSIBinder>()},
                {"RNCNestedScrollViewHeaderNative", std::make_shared<NestedScrollViewHeaderJSIBinder>()},
            };
        }

        ComponentNapiBinderByString createComponentNapiBinderByName() override {
            return {
                {"RNCNestedScrollView", std::make_shared<NestedScrollViewNapiBinder>()},
                {"RNCNestedScrollViewHeaderNative", std::make_shared<NestedScrollViewHeaderNapiBinder>()},
                
            };
        }
        EventEmitRequestHandlers createEventEmitRequestHandlers() override {
            LOG(INFO)<<"liqi LIQIonScroll======NestedScrollViewPackage onScroll";
            return {
                std::make_shared<NestedScrollViewEmitRequestHandler>(), 
                std::make_shared<NestedScrollViewHeaderEmitRequestHandler>()};
        }
    };
} // namespace rnoh
#endif
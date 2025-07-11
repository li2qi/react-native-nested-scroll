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

#include "Props.h"
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>

namespace facebook {
namespace react {

RNCNestedScrollViewProps::RNCNestedScrollViewProps(const PropsParserContext &context, const RNCNestedScrollViewProps &sourceProps,
                                           const RawProps &rawProps)
    : ViewProps(context, sourceProps, rawProps), 
      bounces(convertRawProp(context, rawProps, "bounces", sourceProps.bounces, {false})){}
      
RNCNestedScrollViewHeaderProps::RNCNestedScrollViewHeaderProps(const PropsParserContext &context,
                                                   const RNCNestedScrollViewHeaderProps &sourceProps,
                                                   const RawProps &rawProps)
    : ViewProps(context, sourceProps, rawProps), 
      stickyHeight(convertRawProp(context, rawProps, "stickyHeight", sourceProps.stickyHeight, {-1})),
      stickyHeaderBeginIndex(convertRawProp(context, rawProps, "stickyHeaderBeginIndex", sourceProps.stickyHeaderBeginIndex, {-1}))
    {}
} // namespace react
} // namespace facebook
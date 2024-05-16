/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Chat/Domain/Iterator/DescribeMessagesIterator.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Room.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Chat::Domain::Iterator
{
    class FDescribeMessagesStartAt : public Gs2Object
    {
    public:
        int64 Value;

        explicit FDescribeMessagesStartAt(
            int64& Value
        );
        virtual ~FDescribeMessagesStartAt() override = default;
    
        static FString TypeName;
    };
    typedef TSharedPtr<FDescribeMessagesStartAt> FDescribeMessageStartAtPtr;
}
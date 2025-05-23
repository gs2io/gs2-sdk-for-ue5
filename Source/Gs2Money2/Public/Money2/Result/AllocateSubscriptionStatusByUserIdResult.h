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

#include "CoreMinimal.h"
#include "../Model/SubscriptionStatus.h"

namespace Gs2::Money2::Result
{
    class GS2MONEY2_API FAllocateSubscriptionStatusByUserIdResult final : public TSharedFromThis<FAllocateSubscriptionStatusByUserIdResult>
    {
        TSharedPtr<Model::FSubscriptionStatus> ItemValue;
        
    public:
        
        FAllocateSubscriptionStatusByUserIdResult();
        FAllocateSubscriptionStatusByUserIdResult(
            const FAllocateSubscriptionStatusByUserIdResult& From
        );
        ~FAllocateSubscriptionStatusByUserIdResult() = default;

        TSharedPtr<FAllocateSubscriptionStatusByUserIdResult> WithItem(const TSharedPtr<Model::FSubscriptionStatus> Item);

        TSharedPtr<Model::FSubscriptionStatus> GetItem() const;

        static TSharedPtr<FAllocateSubscriptionStatusByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAllocateSubscriptionStatusByUserIdResult, ESPMode::ThreadSafe> FAllocateSubscriptionStatusByUserIdResultPtr;
}
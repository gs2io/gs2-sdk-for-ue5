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
#include "../Model/SubscribeUser.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FAddSubscribeByUserIdResult final : public TSharedFromThis<FAddSubscribeByUserIdResult>
    {
        TSharedPtr<Model::FSubscribeUser> ItemValue;
        
    public:
        
        FAddSubscribeByUserIdResult();
        FAddSubscribeByUserIdResult(
            const FAddSubscribeByUserIdResult& From
        );
        ~FAddSubscribeByUserIdResult() = default;

        TSharedPtr<FAddSubscribeByUserIdResult> WithItem(const TSharedPtr<Model::FSubscribeUser> Item);

        TSharedPtr<Model::FSubscribeUser> GetItem() const;

        static TSharedPtr<FAddSubscribeByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddSubscribeByUserIdResult, ESPMode::ThreadSafe> FAddSubscribeByUserIdResultPtr;
}
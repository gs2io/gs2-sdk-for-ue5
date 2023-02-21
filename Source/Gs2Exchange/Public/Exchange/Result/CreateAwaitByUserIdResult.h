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
#include "../Model/Await.h"

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FCreateAwaitByUserIdResult final : public TSharedFromThis<FCreateAwaitByUserIdResult>
    {
        TSharedPtr<Model::FAwait> ItemValue;
        TOptional<int64> UnlockAtValue;
        
    public:
        
        FCreateAwaitByUserIdResult();
        FCreateAwaitByUserIdResult(
            const FCreateAwaitByUserIdResult& From
        );
        ~FCreateAwaitByUserIdResult() = default;

        TSharedPtr<FCreateAwaitByUserIdResult> WithItem(const TSharedPtr<Model::FAwait> Item);
        TSharedPtr<FCreateAwaitByUserIdResult> WithUnlockAt(const TOptional<int64> UnlockAt);

        TSharedPtr<Model::FAwait> GetItem() const;
        TOptional<int64> GetUnlockAt() const;
        FString GetUnlockAtString() const;

        static TSharedPtr<FCreateAwaitByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateAwaitByUserIdResult, ESPMode::ThreadSafe> FCreateAwaitByUserIdResultPtr;
}
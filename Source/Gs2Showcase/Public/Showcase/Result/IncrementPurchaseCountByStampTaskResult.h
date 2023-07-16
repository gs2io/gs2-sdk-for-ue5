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
#include "../Model/RandomDisplayItem.h"

namespace Gs2::Showcase::Result
{
    class GS2SHOWCASE_API FIncrementPurchaseCountByStampTaskResult final : public TSharedFromThis<FIncrementPurchaseCountByStampTaskResult>
    {
        TSharedPtr<Model::FRandomDisplayItem> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FIncrementPurchaseCountByStampTaskResult();
        FIncrementPurchaseCountByStampTaskResult(
            const FIncrementPurchaseCountByStampTaskResult& From
        );
        ~FIncrementPurchaseCountByStampTaskResult() = default;

        TSharedPtr<FIncrementPurchaseCountByStampTaskResult> WithItem(const TSharedPtr<Model::FRandomDisplayItem> Item);
        TSharedPtr<FIncrementPurchaseCountByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FRandomDisplayItem> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FIncrementPurchaseCountByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncrementPurchaseCountByStampTaskResult, ESPMode::ThreadSafe> FIncrementPurchaseCountByStampTaskResultPtr;
}
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
#include "../Model/Wallet.h"

namespace Gs2::Money::Result
{
    class GS2MONEY_API FWithdrawByStampTaskResult final : public TSharedFromThis<FWithdrawByStampTaskResult>
    {
        TSharedPtr<Model::FWallet> ItemValue;
        TOptional<float> PriceValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FWithdrawByStampTaskResult();
        FWithdrawByStampTaskResult(
            const FWithdrawByStampTaskResult& From
        );
        ~FWithdrawByStampTaskResult() = default;

        TSharedPtr<FWithdrawByStampTaskResult> WithItem(const TSharedPtr<Model::FWallet> Item);
        TSharedPtr<FWithdrawByStampTaskResult> WithPrice(const TOptional<float> Price);
        TSharedPtr<FWithdrawByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FWallet> GetItem() const;
        TOptional<float> GetPrice() const;
        FString GetPriceString() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FWithdrawByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FWithdrawByStampTaskResult, ESPMode::ThreadSafe> FWithdrawByStampTaskResultPtr;
}
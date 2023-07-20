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
#include "../Model/BalanceParameterStatus.h"

namespace Gs2::Enchant::Result
{
    class GS2ENCHANT_API FGetBalanceParameterStatusByUserIdResult final : public TSharedFromThis<FGetBalanceParameterStatusByUserIdResult>
    {
        TSharedPtr<Model::FBalanceParameterStatus> ItemValue;
        
    public:
        
        FGetBalanceParameterStatusByUserIdResult();
        FGetBalanceParameterStatusByUserIdResult(
            const FGetBalanceParameterStatusByUserIdResult& From
        );
        ~FGetBalanceParameterStatusByUserIdResult() = default;

        TSharedPtr<FGetBalanceParameterStatusByUserIdResult> WithItem(const TSharedPtr<Model::FBalanceParameterStatus> Item);

        TSharedPtr<Model::FBalanceParameterStatus> GetItem() const;

        static TSharedPtr<FGetBalanceParameterStatusByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBalanceParameterStatusByUserIdResult, ESPMode::ThreadSafe> FGetBalanceParameterStatusByUserIdResultPtr;
}
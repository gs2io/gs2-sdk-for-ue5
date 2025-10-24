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
#include "../Model/TransactionResult.h"

namespace Gs2::Distributor::Result
{
    class GS2DISTRIBUTOR_API FIfExpressionByUserIdResult final : public TSharedFromThis<FIfExpressionByUserIdResult>
    {
        TSharedPtr<Model::FTransactionResult> ItemValue;
        TOptional<bool> ExpressionResultValue;
        
    public:
        
        FIfExpressionByUserIdResult();
        FIfExpressionByUserIdResult(
            const FIfExpressionByUserIdResult& From
        );
        ~FIfExpressionByUserIdResult() = default;

        TSharedPtr<FIfExpressionByUserIdResult> WithItem(const TSharedPtr<Model::FTransactionResult> Item);
        TSharedPtr<FIfExpressionByUserIdResult> WithExpressionResult(const TOptional<bool> ExpressionResult);

        TSharedPtr<Model::FTransactionResult> GetItem() const;
        TOptional<bool> GetExpressionResult() const;
        FString GetExpressionResultString() const;

        static TSharedPtr<FIfExpressionByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIfExpressionByUserIdResult, ESPMode::ThreadSafe> FIfExpressionByUserIdResultPtr;
}
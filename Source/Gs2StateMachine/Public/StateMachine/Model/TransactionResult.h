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
#include "Core/Gs2Object.h"
#include "VerifyActionResult.h"
#include "ConsumeActionResult.h"
#include "AcquireActionResult.h"

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FTransactionResult final : public FGs2Object, public TSharedFromThis<FTransactionResult>
    {
        TOptional<FString> TransactionIdValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyActionResult>>> VerifyResultsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeActionResult>>> ConsumeResultsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionResult>>> AcquireResultsValue;
        TOptional<bool> HasErrorValue;

    public:
        FTransactionResult();
        FTransactionResult(
            const FTransactionResult& From
        );
        virtual ~FTransactionResult() override = default;

        TSharedPtr<FTransactionResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FTransactionResult> WithVerifyResults(const TSharedPtr<TArray<TSharedPtr<FVerifyActionResult>>> VerifyResults);
        TSharedPtr<FTransactionResult> WithConsumeResults(const TSharedPtr<TArray<TSharedPtr<FConsumeActionResult>>> ConsumeResults);
        TSharedPtr<FTransactionResult> WithAcquireResults(const TSharedPtr<TArray<TSharedPtr<FAcquireActionResult>>> AcquireResults);
        TSharedPtr<FTransactionResult> WithHasError(const TOptional<bool> HasError);

        TOptional<FString> GetTransactionId() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyActionResult>>> GetVerifyResults() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeActionResult>>> GetConsumeResults() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionResult>>> GetAcquireResults() const;
        TOptional<bool> GetHasError() const;
        FString GetHasErrorString() const;


        static TSharedPtr<FTransactionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTransactionResult, ESPMode::ThreadSafe> FTransactionResultPtr;
}
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
#include "StateMachine/Model/TransactionResult.h"
#include "Gs2StateMachineEzVerifyActionResult.h"
#include "Gs2StateMachineEzConsumeActionResult.h"
#include "Gs2StateMachineEzAcquireActionResult.h"

namespace Gs2::UE5::StateMachine::Model
{
	class EZGS2_API FEzTransactionResult final : public TSharedFromThis<FEzTransactionResult>
	{
        TOptional<FString> TransactionIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVerifyActionResult>>> VerifyResultsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzConsumeActionResult>>> ConsumeResultsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzAcquireActionResult>>> AcquireResultsValue;

	public:
        TSharedPtr<FEzTransactionResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEzTransactionResult> WithVerifyResults(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVerifyActionResult>>> VerifyResults);
        TSharedPtr<FEzTransactionResult> WithConsumeResults(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzConsumeActionResult>>> ConsumeResults);
        TSharedPtr<FEzTransactionResult> WithAcquireResults(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzAcquireActionResult>>> AcquireResults);

        TOptional<FString> GetTransactionId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzVerifyActionResult>>> GetVerifyResults() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzConsumeActionResult>>> GetConsumeResults() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::StateMachine::Model::FEzAcquireActionResult>>> GetAcquireResults() const;

        Gs2::StateMachine::Model::FTransactionResultPtr ToModel() const;
        static TSharedPtr<FEzTransactionResult> FromModel(Gs2::StateMachine::Model::FTransactionResultPtr Model);
    };
    typedef TSharedPtr<FEzTransactionResult> FEzTransactionResultPtr;
}
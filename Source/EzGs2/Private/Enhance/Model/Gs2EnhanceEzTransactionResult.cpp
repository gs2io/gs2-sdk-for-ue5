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

#include "Enhance/Model/Gs2EnhanceEzTransactionResult.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzTransactionResult> FEzTransactionResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEzTransactionResult> FEzTransactionResult::WithVerifyResults(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Core::Model::FEzVerifyActionResult>>> VerifyResults
    )
    {
        this->VerifyResultsValue = VerifyResults;
        return SharedThis(this);
    }

    TSharedPtr<FEzTransactionResult> FEzTransactionResult::WithConsumeResults(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Core::Model::FEzConsumeActionResult>>> ConsumeResults
    )
    {
        this->ConsumeResultsValue = ConsumeResults;
        return SharedThis(this);
    }

    TSharedPtr<FEzTransactionResult> FEzTransactionResult::WithAcquireResults(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Core::Model::FEzAcquireActionResult>>> AcquireResults
    )
    {
        this->AcquireResultsValue = AcquireResults;
        return SharedThis(this);
    }
    TOptional<FString> FEzTransactionResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Core::Model::FEzVerifyActionResult>>> FEzTransactionResult::GetVerifyResults() const
    {
        return VerifyResultsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Core::Model::FEzConsumeActionResult>>> FEzTransactionResult::GetConsumeResults() const
    {
        return ConsumeResultsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Core::Model::FEzAcquireActionResult>>> FEzTransactionResult::GetAcquireResults() const
    {
        return AcquireResultsValue;
    }

    Gs2::Enhance::Model::FTransactionResultPtr FEzTransactionResult::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FTransactionResult>()
            ->WithTransactionId(TransactionIdValue)
            ->WithVerifyResults([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FVerifyActionResult>>>();
                    if (VerifyResultsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *VerifyResultsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithConsumeResults([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FConsumeActionResult>>>();
                    if (ConsumeResultsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConsumeResultsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithAcquireResults([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FAcquireActionResult>>>();
                    if (AcquireResultsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AcquireResultsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzTransactionResult> FEzTransactionResult::FromModel(const Gs2::Enhance::Model::FTransactionResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTransactionResult>()
            ->WithTransactionId(Model->GetTransactionId())
            ->WithVerifyResults([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzVerifyActionResult>>>();
                    if (Model->GetVerifyResults() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetVerifyResults())
                    {
                        v->Add(FEzVerifyActionResult::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithConsumeResults([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeActionResult>>>();
                    if (Model->GetConsumeResults() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConsumeResults())
                    {
                        v->Add(FEzConsumeActionResult::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithAcquireResults([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireActionResult>>>();
                    if (Model->GetAcquireResults() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAcquireResults())
                    {
                        v->Add(FEzAcquireActionResult::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}
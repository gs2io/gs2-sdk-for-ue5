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

#include "Distributor/Model/Gs2DistributorEzStampSheetResult.h"

namespace Gs2::UE5::Distributor::Model
{

    TSharedPtr<FEzStampSheetResult> FEzStampSheetResult::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEzStampSheetResult> FEzStampSheetResult::WithTaskRequests(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzConsumeAction>>> TaskRequests
    )
    {
        this->TaskRequestsValue = TaskRequests;
        return SharedThis(this);
    }

    TSharedPtr<FEzStampSheetResult> FEzStampSheetResult::WithSheetRequest(
        const TSharedPtr<Gs2::UE5::Distributor::Model::FEzAcquireAction> SheetRequest
    )
    {
        this->SheetRequestValue = SheetRequest;
        return SharedThis(this);
    }

    TSharedPtr<FEzStampSheetResult> FEzStampSheetResult::WithTaskResults(
        const TSharedPtr<TArray<FString>> TaskResults
    )
    {
        this->TaskResultsValue = TaskResults;
        return SharedThis(this);
    }

    TSharedPtr<FEzStampSheetResult> FEzStampSheetResult::WithSheetResult(
        const TOptional<FString> SheetResult
    )
    {
        this->SheetResultValue = SheetResult;
        return SharedThis(this);
    }
    TOptional<FString> FEzStampSheetResult::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzConsumeAction>>> FEzStampSheetResult::GetTaskRequests() const
    {
        return TaskRequestsValue;
    }
    TSharedPtr<Gs2::UE5::Distributor::Model::FEzAcquireAction> FEzStampSheetResult::GetSheetRequest() const
    {
        return SheetRequestValue;
    }
    TSharedPtr<TArray<FString>> FEzStampSheetResult::GetTaskResults() const
    {
        return TaskResultsValue;
    }
    TOptional<FString> FEzStampSheetResult::GetSheetResult() const
    {
        return SheetResultValue;
    }

    Gs2::Distributor::Model::FStampSheetResultPtr FEzStampSheetResult::ToModel() const
    {
        return MakeShared<Gs2::Distributor::Model::FStampSheetResult>()
            ->WithTransactionId(TransactionIdValue)
            ->WithTaskRequests([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Distributor::Model::FConsumeAction>>>();
                    if (TaskRequestsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *TaskRequestsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithSheetRequest(SheetRequestValue == nullptr ? nullptr : SheetRequestValue->ToModel())
            ->WithTaskResults(TaskResultsValue)
            ->WithSheetResult(SheetResultValue);
    }

    TSharedPtr<FEzStampSheetResult> FEzStampSheetResult::FromModel(const Gs2::Distributor::Model::FStampSheetResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStampSheetResult>()
            ->WithTransactionId(Model->GetTransactionId())
            ->WithTaskRequests([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeAction>>>();
                    if (Model->GetTaskRequests() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetTaskRequests())
                    {
                        v->Add(FEzConsumeAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithSheetRequest(Model->GetSheetRequest() != nullptr ? Gs2::UE5::Distributor::Model::FEzAcquireAction::FromModel(Model->GetSheetRequest()) : nullptr)
            ->WithTaskResults(Model->GetTaskResults())
            ->WithSheetResult(Model->GetSheetResult());
    }
}
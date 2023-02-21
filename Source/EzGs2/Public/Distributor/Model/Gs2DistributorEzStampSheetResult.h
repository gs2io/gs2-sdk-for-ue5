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
#include "Distributor/Model/StampSheetResult.h"
#include "Gs2DistributorEzConsumeAction.h"
#include "Gs2DistributorEzAcquireAction.h"

namespace Gs2::UE5::Distributor::Model
{
	class EZGS2_API FEzStampSheetResult final : public TSharedFromThis<FEzStampSheetResult>
	{
        TOptional<FString> TransactionIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzConsumeAction>>> TaskRequestsValue;
        TSharedPtr<Gs2::UE5::Distributor::Model::FEzAcquireAction> SheetRequestValue;
        TSharedPtr<TArray<FString>> TaskResultsValue;
        TOptional<FString> SheetResultValue;

	public:
        TSharedPtr<FEzStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEzStampSheetResult> WithTaskRequests(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzConsumeAction>>> TaskRequests);
        TSharedPtr<FEzStampSheetResult> WithSheetRequest(const TSharedPtr<Gs2::UE5::Distributor::Model::FEzAcquireAction> SheetRequest);
        TSharedPtr<FEzStampSheetResult> WithTaskResults(const TSharedPtr<TArray<FString>> TaskResults);
        TSharedPtr<FEzStampSheetResult> WithSheetResult(const TOptional<FString> SheetResult);

        TOptional<FString> GetTransactionId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzConsumeAction>>> GetTaskRequests() const;

        TSharedPtr<Gs2::UE5::Distributor::Model::FEzAcquireAction> GetSheetRequest() const;

        TSharedPtr<TArray<FString>> GetTaskResults() const;

        TOptional<FString> GetSheetResult() const;

        Gs2::Distributor::Model::FStampSheetResultPtr ToModel() const;
        static TSharedPtr<FEzStampSheetResult> FromModel(Gs2::Distributor::Model::FStampSheetResultPtr Model);
    };
    typedef TSharedPtr<FEzStampSheetResult> FEzStampSheetResultPtr;
}
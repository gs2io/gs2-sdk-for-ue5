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
#include "Money2/Model/WalletSummary.h"

namespace Gs2::UE5::Money2::Model
{
	class EZGS2_API FEzWalletSummary final : public TSharedFromThis<FEzWalletSummary>
	{
        TOptional<int32> PaidValue;
        TOptional<int32> FreeValue;
        TOptional<int32> TotalValue;

	public:
        TSharedPtr<FEzWalletSummary> WithPaid(const TOptional<int32> Paid);
        TSharedPtr<FEzWalletSummary> WithFree(const TOptional<int32> Free);
        TSharedPtr<FEzWalletSummary> WithTotal(const TOptional<int32> Total);

        TOptional<int32> GetPaid() const;
        FString GetPaidString() const;

        TOptional<int32> GetFree() const;
        FString GetFreeString() const;

        TOptional<int32> GetTotal() const;
        FString GetTotalString() const;

        Gs2::Money2::Model::FWalletSummaryPtr ToModel() const;
        static TSharedPtr<FEzWalletSummary> FromModel(Gs2::Money2::Model::FWalletSummaryPtr Model);
    };
    typedef TSharedPtr<FEzWalletSummary> FEzWalletSummaryPtr;
}
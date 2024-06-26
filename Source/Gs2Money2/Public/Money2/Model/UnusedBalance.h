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

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FUnusedBalance final : public Gs2Object, public TSharedFromThis<FUnusedBalance>
    {
        TOptional<FString> UnusedBalanceIdValue;
        TOptional<FString> CurrencyValue;
        TOptional<float> BalanceValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FUnusedBalance();
        FUnusedBalance(
            const FUnusedBalance& From
        );
        virtual ~FUnusedBalance() override = default;

        TSharedPtr<FUnusedBalance> WithUnusedBalanceId(const TOptional<FString> UnusedBalanceId);
        TSharedPtr<FUnusedBalance> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FUnusedBalance> WithBalance(const TOptional<float> Balance);
        TSharedPtr<FUnusedBalance> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FUnusedBalance> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetUnusedBalanceId() const;
        TOptional<FString> GetCurrency() const;
        TOptional<float> GetBalance() const;
        FString GetBalanceString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCurrencyFromGrn(const FString Grn);

        static TSharedPtr<FUnusedBalance> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnusedBalance, ESPMode::ThreadSafe> FUnusedBalancePtr;
}
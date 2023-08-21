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
#include "ConsumeAction.h"
#include "AcquireAction.h"

namespace Gs2::Exchange::Model
{
    class GS2EXCHANGE_API FIncrementalRateModelMaster final : public Gs2Object, public TSharedFromThis<FIncrementalRateModelMaster>
    {
        TOptional<FString> IncrementalRateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FConsumeAction> ConsumeActionValue;
        TOptional<FString> CalculateTypeValue;
        TOptional<int64> BaseValueValue;
        TOptional<int64> CoefficientValueValue;
        TOptional<FString> CalculateScriptIdValue;
        TOptional<FString> ExchangeCountIdValue;
        TOptional<int32> MaximumExchangeCountValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FIncrementalRateModelMaster();
        FIncrementalRateModelMaster(
            const FIncrementalRateModelMaster& From
        );
        virtual ~FIncrementalRateModelMaster() override = default;

        TSharedPtr<FIncrementalRateModelMaster> WithIncrementalRateModelId(const TOptional<FString> IncrementalRateModelId);
        TSharedPtr<FIncrementalRateModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FIncrementalRateModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FIncrementalRateModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FIncrementalRateModelMaster> WithConsumeAction(const TSharedPtr<FConsumeAction> ConsumeAction);
        TSharedPtr<FIncrementalRateModelMaster> WithCalculateType(const TOptional<FString> CalculateType);
        TSharedPtr<FIncrementalRateModelMaster> WithBaseValue(const TOptional<int64> BaseValue);
        TSharedPtr<FIncrementalRateModelMaster> WithCoefficientValue(const TOptional<int64> CoefficientValue);
        TSharedPtr<FIncrementalRateModelMaster> WithCalculateScriptId(const TOptional<FString> CalculateScriptId);
        TSharedPtr<FIncrementalRateModelMaster> WithExchangeCountId(const TOptional<FString> ExchangeCountId);
        TSharedPtr<FIncrementalRateModelMaster> WithMaximumExchangeCount(const TOptional<int32> MaximumExchangeCount);
        TSharedPtr<FIncrementalRateModelMaster> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FIncrementalRateModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FIncrementalRateModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FIncrementalRateModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetIncrementalRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FConsumeAction> GetConsumeAction() const;
        TOptional<FString> GetCalculateType() const;
        TOptional<int64> GetBaseValue() const;
        FString GetBaseValueString() const;
        TOptional<int64> GetCoefficientValue() const;
        FString GetCoefficientValueString() const;
        TOptional<FString> GetCalculateScriptId() const;
        TOptional<FString> GetExchangeCountId() const;
        TOptional<int32> GetMaximumExchangeCount() const;
        FString GetMaximumExchangeCountString() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRateNameFromGrn(const FString Grn);

        static TSharedPtr<FIncrementalRateModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FIncrementalRateModelMaster, ESPMode::ThreadSafe> FIncrementalRateModelMasterPtr;
}
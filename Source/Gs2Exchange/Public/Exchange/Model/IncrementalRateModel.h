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
    class GS2EXCHANGE_API FIncrementalRateModel final : public Gs2Object, public TSharedFromThis<FIncrementalRateModel>
    {
        TOptional<FString> IncrementalRateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FConsumeAction> ConsumeActionValue;
        TOptional<FString> CalculateTypeValue;
        TOptional<int64> BaseValueValue;
        TOptional<int64> CoefficientValueValue;
        TOptional<FString> CalculateScriptIdValue;
        TOptional<FString> ExchangeCountIdValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;

    public:
        FIncrementalRateModel();
        FIncrementalRateModel(
            const FIncrementalRateModel& From
        );
        virtual ~FIncrementalRateModel() override = default;

        TSharedPtr<FIncrementalRateModel> WithIncrementalRateModelId(const TOptional<FString> IncrementalRateModelId);
        TSharedPtr<FIncrementalRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FIncrementalRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FIncrementalRateModel> WithConsumeAction(const TSharedPtr<FConsumeAction> ConsumeAction);
        TSharedPtr<FIncrementalRateModel> WithCalculateType(const TOptional<FString> CalculateType);
        TSharedPtr<FIncrementalRateModel> WithBaseValue(const TOptional<int64> BaseValue);
        TSharedPtr<FIncrementalRateModel> WithCoefficientValue(const TOptional<int64> CoefficientValue);
        TSharedPtr<FIncrementalRateModel> WithCalculateScriptId(const TOptional<FString> CalculateScriptId);
        TSharedPtr<FIncrementalRateModel> WithExchangeCountId(const TOptional<FString> ExchangeCountId);
        TSharedPtr<FIncrementalRateModel> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);

        TOptional<FString> GetIncrementalRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FConsumeAction> GetConsumeAction() const;
        TOptional<FString> GetCalculateType() const;
        TOptional<int64> GetBaseValue() const;
        FString GetBaseValueString() const;
        TOptional<int64> GetCoefficientValue() const;
        FString GetCoefficientValueString() const;
        TOptional<FString> GetCalculateScriptId() const;
        TOptional<FString> GetExchangeCountId() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRateNameFromGrn(const FString Grn);

        static TSharedPtr<FIncrementalRateModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FIncrementalRateModel, ESPMode::ThreadSafe> FIncrementalRateModelPtr;
}
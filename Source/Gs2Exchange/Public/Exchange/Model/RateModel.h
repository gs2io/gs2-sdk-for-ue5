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
#include "VerifyAction.h"
#include "ConsumeAction.h"
#include "AcquireAction.h"

namespace Gs2::Exchange::Model
{
    class GS2EXCHANGE_API FRateModel final : public FGs2Object, public TSharedFromThis<FRateModel>
    {
        TOptional<FString> RateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TOptional<FString> TimingTypeValue;
        TOptional<int32> LockTimeValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;

    public:
        FRateModel();
        FRateModel(
            const FRateModel& From
        );
        virtual ~FRateModel() override = default;

        TSharedPtr<FRateModel> WithRateModelId(const TOptional<FString> RateModelId);
        TSharedPtr<FRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRateModel> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActions);
        TSharedPtr<FRateModel> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FRateModel> WithTimingType(const TOptional<FString> TimingType);
        TSharedPtr<FRateModel> WithLockTime(const TOptional<int32> LockTime);
        TSharedPtr<FRateModel> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);

        TOptional<FString> GetRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> GetVerifyActions() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TOptional<FString> GetTimingType() const;
        TOptional<int32> GetLockTime() const;
        FString GetLockTimeString() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRateNameFromGrn(const FString Grn);

        static TSharedPtr<FRateModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRateModel, ESPMode::ThreadSafe> FRateModelPtr;
}
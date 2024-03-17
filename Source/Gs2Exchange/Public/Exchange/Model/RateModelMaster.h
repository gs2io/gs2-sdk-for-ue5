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
    class GS2EXCHANGE_API FRateModelMaster final : public Gs2Object, public TSharedFromThis<FRateModelMaster>
    {
        TOptional<FString> RateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TOptional<FString> TimingTypeValue;
        TOptional<int32> LockTimeValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRateModelMaster();
        FRateModelMaster(
            const FRateModelMaster& From
        );
        virtual ~FRateModelMaster() override = default;

        TSharedPtr<FRateModelMaster> WithRateModelId(const TOptional<FString> RateModelId);
        TSharedPtr<FRateModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FRateModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FRateModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRateModelMaster> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FRateModelMaster> WithTimingType(const TOptional<FString> TimingType);
        TSharedPtr<FRateModelMaster> WithLockTime(const TOptional<int32> LockTime);
        TSharedPtr<FRateModelMaster> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FRateModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRateModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRateModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TOptional<FString> GetTimingType() const;
        TOptional<int32> GetLockTime() const;
        FString GetLockTimeString() const;
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

        static TSharedPtr<FRateModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRateModelMaster, ESPMode::ThreadSafe> FRateModelMasterPtr;
}
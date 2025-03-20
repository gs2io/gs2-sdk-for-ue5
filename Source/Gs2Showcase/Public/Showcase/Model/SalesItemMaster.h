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

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FSalesItemMaster final : public FGs2Object, public TSharedFromThis<FSalesItemMaster>
    {
        TOptional<FString> SalesItemIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSalesItemMaster();
        FSalesItemMaster(
            const FSalesItemMaster& From
        );
        virtual ~FSalesItemMaster() override = default;

        TSharedPtr<FSalesItemMaster> WithSalesItemId(const TOptional<FString> SalesItemId);
        TSharedPtr<FSalesItemMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FSalesItemMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FSalesItemMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSalesItemMaster> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActions);
        TSharedPtr<FSalesItemMaster> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FSalesItemMaster> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FSalesItemMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSalesItemMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSalesItemMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSalesItemId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> GetVerifyActions() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
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
        static TOptional<FString> GetSalesItemNameFromGrn(const FString Grn);

        static TSharedPtr<FSalesItemMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSalesItemMaster, ESPMode::ThreadSafe> FSalesItemMasterPtr;
}
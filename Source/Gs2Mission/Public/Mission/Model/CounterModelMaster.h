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
#include "CounterScopeModel.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FCounterModelMaster final : public FGs2Object, public TSharedFromThis<FCounterModelMaster>
    {
        TOptional<FString> CounterIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<TArray<TSharedPtr<FCounterScopeModel>>> ScopesValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FCounterModelMaster();
        FCounterModelMaster(
            const FCounterModelMaster& From
        );
        virtual ~FCounterModelMaster() override = default;

        TSharedPtr<FCounterModelMaster> WithCounterId(const TOptional<FString> CounterId);
        TSharedPtr<FCounterModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FCounterModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCounterModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCounterModelMaster> WithScopes(const TSharedPtr<TArray<TSharedPtr<FCounterScopeModel>>> Scopes);
        TSharedPtr<FCounterModelMaster> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FCounterModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCounterModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FCounterModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetCounterId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<TArray<TSharedPtr<FCounterScopeModel>>> GetScopes() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCounterNameFromGrn(const FString Grn);

        static TSharedPtr<FCounterModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCounterModelMaster, ESPMode::ThreadSafe> FCounterModelMasterPtr;
}
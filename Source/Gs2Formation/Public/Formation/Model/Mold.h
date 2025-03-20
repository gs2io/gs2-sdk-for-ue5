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

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FMold final : public FGs2Object, public TSharedFromThis<FMold>
    {
        TOptional<FString> MoldIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CapacityValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FMold();
        FMold(
            const FMold& From
        );
        virtual ~FMold() override = default;

        TSharedPtr<FMold> WithMoldId(const TOptional<FString> MoldId);
        TSharedPtr<FMold> WithName(const TOptional<FString> Name);
        TSharedPtr<FMold> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMold> WithCapacity(const TOptional<int32> Capacity);
        TSharedPtr<FMold> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FMold> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FMold> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetMoldId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetMoldModelNameFromGrn(const FString Grn);

        static TSharedPtr<FMold> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMold, ESPMode::ThreadSafe> FMoldPtr;
}
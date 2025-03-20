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

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FPlatformId final : public FGs2Object, public TSharedFromThis<FPlatformId>
    {
        TOptional<FString> PlatformIdValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FPlatformId();
        FPlatformId(
            const FPlatformId& From
        );
        virtual ~FPlatformId() override = default;

        TSharedPtr<FPlatformId> WithPlatformId(const TOptional<FString> PlatformId);
        TSharedPtr<FPlatformId> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPlatformId> WithType(const TOptional<int32> Type);
        TSharedPtr<FPlatformId> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FPlatformId> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPlatformId> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetPlatformId() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetUserIdentifier() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetTypeFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdentifierFromGrn(const FString Grn);

        static TSharedPtr<FPlatformId> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPlatformId, ESPMode::ThreadSafe> FPlatformIdPtr;
}
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
#include "Version.h"

namespace Gs2::Version::Model
{
    class GS2VERSION_API FAcceptVersion final : public FGs2Object, public TSharedFromThis<FAcceptVersion>
    {
        TOptional<FString> AcceptVersionIdValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<FVersion> VersionValue;
        TOptional<FString> StatusValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FAcceptVersion();
        FAcceptVersion(
            const FAcceptVersion& From
        );
        virtual ~FAcceptVersion() override = default;

        TSharedPtr<FAcceptVersion> WithAcceptVersionId(const TOptional<FString> AcceptVersionId);
        TSharedPtr<FAcceptVersion> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FAcceptVersion> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcceptVersion> WithVersion(const TSharedPtr<FVersion> Version);
        TSharedPtr<FAcceptVersion> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FAcceptVersion> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FAcceptVersion> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FAcceptVersion> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetAcceptVersionId() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<FVersion> GetVersion() const;
        TOptional<FString> GetStatus() const;
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
        static TOptional<FString> GetVersionNameFromGrn(const FString Grn);

        static TSharedPtr<FAcceptVersion> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAcceptVersion, ESPMode::ThreadSafe> FAcceptVersionPtr;
}
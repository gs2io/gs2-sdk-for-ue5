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

namespace Gs2::Friend::Model
{
    class GS2FRIEND_API FProfile final : public TSharedFromThis<FProfile>
    {
        TOptional<FString> ProfileIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FollowerProfileValue;
        TOptional<FString> FriendProfileValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FProfile();
        FProfile(
            const FProfile& From
        );
        ~FProfile() = default;

        TSharedPtr<FProfile> WithProfileId(const TOptional<FString> ProfileId);
        TSharedPtr<FProfile> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FProfile> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FProfile> WithFollowerProfile(const TOptional<FString> FollowerProfile);
        TSharedPtr<FProfile> WithFriendProfile(const TOptional<FString> FriendProfile);
        TSharedPtr<FProfile> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FProfile> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetProfileId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPublicProfile() const;
        TOptional<FString> GetFollowerProfile() const;
        TOptional<FString> GetFriendProfile() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FProfile> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FProfile, ESPMode::ThreadSafe> FProfilePtr;
}
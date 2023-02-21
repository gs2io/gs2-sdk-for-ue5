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
    class GS2FRIEND_API FFriendUser final : public TSharedFromThis<FFriendUser>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FriendProfileValue;

    public:
        FFriendUser();
        FFriendUser(
            const FFriendUser& From
        );
        ~FFriendUser() = default;

        TSharedPtr<FFriendUser> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FFriendUser> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FFriendUser> WithFriendProfile(const TOptional<FString> FriendProfile);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPublicProfile() const;
        TOptional<FString> GetFriendProfile() const;


        static TSharedPtr<FFriendUser> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFriendUser, ESPMode::ThreadSafe> FFriendUserPtr;
}
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

namespace Gs2::Friend::Model
{
    class GS2FRIEND_API FFriendRequest final : public FGs2Object, public TSharedFromThis<FFriendRequest>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;
        TOptional<FString> PublicProfileValue;

    public:
        FFriendRequest();
        FFriendRequest(
            const FFriendRequest& From
        );
        virtual ~FFriendRequest() override = default;

        TSharedPtr<FFriendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FFriendRequest> WithTargetUserId(const TOptional<FString> TargetUserId);
        TSharedPtr<FFriendRequest> WithPublicProfile(const TOptional<FString> PublicProfile);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;
        TOptional<FString> GetPublicProfile() const;


        static TSharedPtr<FFriendRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFriendRequest, ESPMode::ThreadSafe> FFriendRequestPtr;
}
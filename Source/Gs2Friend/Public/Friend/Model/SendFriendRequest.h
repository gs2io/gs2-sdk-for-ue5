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
    class GS2FRIEND_API FSendFriendRequest final : public Gs2Object, public TSharedFromThis<FSendFriendRequest>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;

    public:
        FSendFriendRequest();
        FSendFriendRequest(
            const FSendFriendRequest& From
        );
        virtual ~FSendFriendRequest() override = default;

        TSharedPtr<FSendFriendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendFriendRequest> WithTargetUserId(const TOptional<FString> TargetUserId);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;


        static TSharedPtr<FSendFriendRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSendFriendRequest, ESPMode::ThreadSafe> FSendFriendRequestPtr;
}
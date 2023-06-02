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
    class GS2FRIEND_API FReceiveFriendRequest final : public Gs2Object, public TSharedFromThis<FReceiveFriendRequest>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;

    public:
        FReceiveFriendRequest();
        FReceiveFriendRequest(
            const FReceiveFriendRequest& From
        );
        virtual ~FReceiveFriendRequest() override = default;

        TSharedPtr<FReceiveFriendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReceiveFriendRequest> WithTargetUserId(const TOptional<FString> TargetUserId);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;


        static TSharedPtr<FReceiveFriendRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FReceiveFriendRequest, ESPMode::ThreadSafe> FReceiveFriendRequestPtr;
}
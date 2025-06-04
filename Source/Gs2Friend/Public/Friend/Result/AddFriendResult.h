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
#include "../Model/FriendUser.h"

namespace Gs2::Friend::Result
{
    class GS2FRIEND_API FAddFriendResult final : public TSharedFromThis<FAddFriendResult>
    {
        TSharedPtr<Model::FFriendUser> ItemValue;
        
    public:
        
        FAddFriendResult();
        FAddFriendResult(
            const FAddFriendResult& From
        );
        ~FAddFriendResult() = default;

        TSharedPtr<FAddFriendResult> WithItem(const TSharedPtr<Model::FFriendUser> Item);

        TSharedPtr<Model::FFriendUser> GetItem() const;

        static TSharedPtr<FAddFriendResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddFriendResult, ESPMode::ThreadSafe> FAddFriendResultPtr;
}
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
#include "../Model/FriendRequest.h"

namespace Gs2::Friend::Result
{
    class GS2FRIEND_API FGetReceiveRequestResult final : public TSharedFromThis<FGetReceiveRequestResult>
    {
        TSharedPtr<Model::FFriendRequest> ItemValue;
        
    public:
        
        FGetReceiveRequestResult();
        FGetReceiveRequestResult(
            const FGetReceiveRequestResult& From
        );
        ~FGetReceiveRequestResult() = default;

        TSharedPtr<FGetReceiveRequestResult> WithItem(const TSharedPtr<Model::FFriendRequest> Item);

        TSharedPtr<Model::FFriendRequest> GetItem() const;

        static TSharedPtr<FGetReceiveRequestResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetReceiveRequestResult, ESPMode::ThreadSafe> FGetReceiveRequestResultPtr;
}
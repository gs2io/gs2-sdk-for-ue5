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
#include "../Model/Room.h"

namespace Gs2::Chat::Result
{
    class GS2CHAT_API FUpdateRoomResult final : public TSharedFromThis<FUpdateRoomResult>
    {
        TSharedPtr<Model::FRoom> ItemValue;
        
    public:
        
        FUpdateRoomResult();
        FUpdateRoomResult(
            const FUpdateRoomResult& From
        );
        ~FUpdateRoomResult() = default;

        TSharedPtr<FUpdateRoomResult> WithItem(const TSharedPtr<Model::FRoom> Item);

        TSharedPtr<Model::FRoom> GetItem() const;

        static TSharedPtr<FUpdateRoomResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRoomResult, ESPMode::ThreadSafe> FUpdateRoomResultPtr;
}
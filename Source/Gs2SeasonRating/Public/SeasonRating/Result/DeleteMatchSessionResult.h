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
#include "../Model/MatchSession.h"

namespace Gs2::SeasonRating::Result
{
    class GS2SEASONRATING_API FDeleteMatchSessionResult final : public TSharedFromThis<FDeleteMatchSessionResult>
    {
        TSharedPtr<Model::FMatchSession> ItemValue;
        
    public:
        
        FDeleteMatchSessionResult();
        FDeleteMatchSessionResult(
            const FDeleteMatchSessionResult& From
        );
        ~FDeleteMatchSessionResult() = default;

        TSharedPtr<FDeleteMatchSessionResult> WithItem(const TSharedPtr<Model::FMatchSession> Item);

        TSharedPtr<Model::FMatchSession> GetItem() const;

        static TSharedPtr<FDeleteMatchSessionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMatchSessionResult, ESPMode::ThreadSafe> FDeleteMatchSessionResultPtr;
}
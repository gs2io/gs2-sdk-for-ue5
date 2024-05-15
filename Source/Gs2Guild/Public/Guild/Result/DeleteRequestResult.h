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
#include "../Model/SendMemberRequest.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FDeleteRequestResult final : public TSharedFromThis<FDeleteRequestResult>
    {
        TSharedPtr<Model::FSendMemberRequest> ItemValue;
        
    public:
        
        FDeleteRequestResult();
        FDeleteRequestResult(
            const FDeleteRequestResult& From
        );
        ~FDeleteRequestResult() = default;

        TSharedPtr<FDeleteRequestResult> WithItem(const TSharedPtr<Model::FSendMemberRequest> Item);

        TSharedPtr<Model::FSendMemberRequest> GetItem() const;

        static TSharedPtr<FDeleteRequestResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteRequestResult, ESPMode::ThreadSafe> FDeleteRequestResultPtr;
}
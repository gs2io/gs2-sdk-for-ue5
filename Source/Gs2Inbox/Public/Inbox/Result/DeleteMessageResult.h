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
#include "../Model/Message.h"

namespace Gs2::Inbox::Result
{
    class GS2INBOX_API FDeleteMessageResult final : public TSharedFromThis<FDeleteMessageResult>
    {
        TSharedPtr<Model::FMessage> ItemValue;
        
    public:
        
        FDeleteMessageResult();
        FDeleteMessageResult(
            const FDeleteMessageResult& From
        );
        ~FDeleteMessageResult() = default;

        TSharedPtr<FDeleteMessageResult> WithItem(const TSharedPtr<Model::FMessage> Item);

        TSharedPtr<Model::FMessage> GetItem() const;

        static TSharedPtr<FDeleteMessageResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMessageResult, ESPMode::ThreadSafe> FDeleteMessageResultPtr;
}
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
    class GS2INBOX_API FDeleteMessageByStampTaskResult final : public TSharedFromThis<FDeleteMessageByStampTaskResult>
    {
        TSharedPtr<Model::FMessage> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FDeleteMessageByStampTaskResult();
        FDeleteMessageByStampTaskResult(
            const FDeleteMessageByStampTaskResult& From
        );
        ~FDeleteMessageByStampTaskResult() = default;

        TSharedPtr<FDeleteMessageByStampTaskResult> WithItem(const TSharedPtr<Model::FMessage> Item);
        TSharedPtr<FDeleteMessageByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FMessage> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FDeleteMessageByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMessageByStampTaskResult, ESPMode::ThreadSafe> FDeleteMessageByStampTaskResultPtr;
}
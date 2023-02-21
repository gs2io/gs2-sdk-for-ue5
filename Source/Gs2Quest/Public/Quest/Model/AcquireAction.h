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

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FAcquireAction final : public TSharedFromThis<FAcquireAction>
    {
        TOptional<FString> ActionValue;
        TOptional<FString> RequestValue;

    public:
        FAcquireAction();
        FAcquireAction(
            const FAcquireAction& From
        );
        ~FAcquireAction() = default;

        TSharedPtr<FAcquireAction> WithAction(const TOptional<FString> Action);
        TSharedPtr<FAcquireAction> WithRequest(const TOptional<FString> Request);

        TOptional<FString> GetAction() const;
        TOptional<FString> GetRequest() const;


        static TSharedPtr<FAcquireAction> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAcquireAction, ESPMode::ThreadSafe> FAcquireActionPtr;
}
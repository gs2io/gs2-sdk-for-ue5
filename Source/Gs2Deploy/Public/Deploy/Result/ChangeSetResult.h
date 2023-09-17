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
#include "../Model/ChangeSet.h"

namespace Gs2::Deploy::Result
{
    class GS2DEPLOY_API FChangeSetResult final : public TSharedFromThis<FChangeSetResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FChangeSet>>> ItemsValue;
        
    public:
        
        FChangeSetResult();
        FChangeSetResult(
            const FChangeSetResult& From
        );
        ~FChangeSetResult() = default;

        TSharedPtr<FChangeSetResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FChangeSet>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FChangeSet>>> GetItems() const;

        static TSharedPtr<FChangeSetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FChangeSetResult, ESPMode::ThreadSafe> FChangeSetResultPtr;
}
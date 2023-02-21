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
#include "../Model/Job.h"

namespace Gs2::JobQueue::Result
{
    class GS2JOBQUEUE_API FPushByUserIdResult final : public TSharedFromThis<FPushByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FJob>>> ItemsValue;
        TOptional<bool> AutoRunValue;
        
    public:
        
        FPushByUserIdResult();
        FPushByUserIdResult(
            const FPushByUserIdResult& From
        );
        ~FPushByUserIdResult() = default;

        TSharedPtr<FPushByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FJob>>> Items);
        TSharedPtr<FPushByUserIdResult> WithAutoRun(const TOptional<bool> AutoRun);

        TSharedPtr<TArray<TSharedPtr<Model::FJob>>> GetItems() const;
        TOptional<bool> GetAutoRun() const;
        FString GetAutoRunString() const;

        static TSharedPtr<FPushByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPushByUserIdResult, ESPMode::ThreadSafe> FPushByUserIdResultPtr;
}
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
#include "../Model/JobResultBody.h"

namespace Gs2::JobQueue::Result
{
    class GS2JOBQUEUE_API FRunByUserIdResult final : public TSharedFromThis<FRunByUserIdResult>
    {
        TSharedPtr<Model::FJob> ItemValue;
        TSharedPtr<Model::FJobResultBody> ResultValue;
        TOptional<bool> IsLastJobValue;
        
    public:
        
        FRunByUserIdResult();
        FRunByUserIdResult(
            const FRunByUserIdResult& From
        );
        ~FRunByUserIdResult() = default;

        TSharedPtr<FRunByUserIdResult> WithItem(const TSharedPtr<Model::FJob> Item);
        TSharedPtr<FRunByUserIdResult> WithResult(const TSharedPtr<Model::FJobResultBody> Result);
        TSharedPtr<FRunByUserIdResult> WithIsLastJob(const TOptional<bool> IsLastJob);

        TSharedPtr<Model::FJob> GetItem() const;
        TSharedPtr<Model::FJobResultBody> GetResult() const;
        TOptional<bool> GetIsLastJob() const;
        FString GetIsLastJobString() const;

        static TSharedPtr<FRunByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunByUserIdResult, ESPMode::ThreadSafe> FRunByUserIdResultPtr;
}
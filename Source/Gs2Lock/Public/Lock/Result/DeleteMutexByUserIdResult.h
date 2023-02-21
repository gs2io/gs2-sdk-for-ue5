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
#include "../Model/Mutex.h"

namespace Gs2::Lock::Result
{
    class GS2LOCK_API FDeleteMutexByUserIdResult final : public TSharedFromThis<FDeleteMutexByUserIdResult>
    {
        TSharedPtr<Model::FMutex> ItemValue;
        
    public:
        
        FDeleteMutexByUserIdResult();
        FDeleteMutexByUserIdResult(
            const FDeleteMutexByUserIdResult& From
        );
        ~FDeleteMutexByUserIdResult() = default;

        TSharedPtr<FDeleteMutexByUserIdResult> WithItem(const TSharedPtr<Model::FMutex> Item);

        TSharedPtr<Model::FMutex> GetItem() const;

        static TSharedPtr<FDeleteMutexByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMutexByUserIdResult, ESPMode::ThreadSafe> FDeleteMutexByUserIdResultPtr;
}
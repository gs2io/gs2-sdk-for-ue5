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

#include "Money2/Result/CheckCleanUserDataByUserIdResult.h"

namespace Gs2::Money2::Result
{
    FCheckCleanUserDataByUserIdResult::FCheckCleanUserDataByUserIdResult()
    {
    }

    FCheckCleanUserDataByUserIdResult::FCheckCleanUserDataByUserIdResult(
        const FCheckCleanUserDataByUserIdResult& From
    )
    {
    }

    TSharedPtr<FCheckCleanUserDataByUserIdResult> FCheckCleanUserDataByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCheckCleanUserDataByUserIdResult>();
    }

    TSharedPtr<FJsonObject> FCheckCleanUserDataByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        return JsonRootObject;
    }
}
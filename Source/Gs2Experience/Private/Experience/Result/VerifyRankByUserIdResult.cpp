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

#include "Experience/Result/VerifyRankByUserIdResult.h"

namespace Gs2::Experience::Result
{
    FVerifyRankByUserIdResult::FVerifyRankByUserIdResult()
    {
    }

    FVerifyRankByUserIdResult::FVerifyRankByUserIdResult(
        const FVerifyRankByUserIdResult& From
    )
    {
    }

    TSharedPtr<FVerifyRankByUserIdResult> FVerifyRankByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyRankByUserIdResult>();
    }

    TSharedPtr<FJsonObject> FVerifyRankByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        return JsonRootObject;
    }
}
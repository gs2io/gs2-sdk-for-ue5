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

#include "Inventory/Result/VerifySimpleItemResult.h"

namespace Gs2::Inventory::Result
{
    FVerifySimpleItemResult::FVerifySimpleItemResult()
    {
    }

    FVerifySimpleItemResult::FVerifySimpleItemResult(
        const FVerifySimpleItemResult& From
    )
    {
    }

    TSharedPtr<FVerifySimpleItemResult> FVerifySimpleItemResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifySimpleItemResult>();
    }

    TSharedPtr<FJsonObject> FVerifySimpleItemResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        return JsonRootObject;
    }
}
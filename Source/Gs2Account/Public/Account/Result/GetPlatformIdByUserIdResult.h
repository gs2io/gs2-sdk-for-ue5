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
#include "../Model/PlatformId.h"

namespace Gs2::Account::Result
{
    class GS2ACCOUNT_API FGetPlatformIdByUserIdResult final : public TSharedFromThis<FGetPlatformIdByUserIdResult>
    {
        TSharedPtr<Model::FPlatformId> ItemValue;
        
    public:
        
        FGetPlatformIdByUserIdResult();
        FGetPlatformIdByUserIdResult(
            const FGetPlatformIdByUserIdResult& From
        );
        ~FGetPlatformIdByUserIdResult() = default;

        TSharedPtr<FGetPlatformIdByUserIdResult> WithItem(const TSharedPtr<Model::FPlatformId> Item);

        TSharedPtr<Model::FPlatformId> GetItem() const;

        static TSharedPtr<FGetPlatformIdByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPlatformIdByUserIdResult, ESPMode::ThreadSafe> FGetPlatformIdByUserIdResultPtr;
}
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
#include "../Model/AcceptVersion.h"

namespace Gs2::Version::Result
{
    class GS2VERSION_API FAcceptByUserIdResult final : public TSharedFromThis<FAcceptByUserIdResult>
    {
        TSharedPtr<Model::FAcceptVersion> ItemValue;
        
    public:
        
        FAcceptByUserIdResult();
        FAcceptByUserIdResult(
            const FAcceptByUserIdResult& From
        );
        ~FAcceptByUserIdResult() = default;

        TSharedPtr<FAcceptByUserIdResult> WithItem(const TSharedPtr<Model::FAcceptVersion> Item);

        TSharedPtr<Model::FAcceptVersion> GetItem() const;

        static TSharedPtr<FAcceptByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcceptByUserIdResult, ESPMode::ThreadSafe> FAcceptByUserIdResultPtr;
}
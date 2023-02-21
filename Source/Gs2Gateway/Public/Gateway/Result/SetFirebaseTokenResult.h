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
#include "../Model/FirebaseToken.h"

namespace Gs2::Gateway::Result
{
    class GS2GATEWAY_API FSetFirebaseTokenResult final : public TSharedFromThis<FSetFirebaseTokenResult>
    {
        TSharedPtr<Model::FFirebaseToken> ItemValue;
        
    public:
        
        FSetFirebaseTokenResult();
        FSetFirebaseTokenResult(
            const FSetFirebaseTokenResult& From
        );
        ~FSetFirebaseTokenResult() = default;

        TSharedPtr<FSetFirebaseTokenResult> WithItem(const TSharedPtr<Model::FFirebaseToken> Item);

        TSharedPtr<Model::FFirebaseToken> GetItem() const;

        static TSharedPtr<FSetFirebaseTokenResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFirebaseTokenResult, ESPMode::ThreadSafe> FSetFirebaseTokenResultPtr;
}
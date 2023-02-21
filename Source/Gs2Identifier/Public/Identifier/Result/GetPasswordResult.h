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
#include "../Model/Password.h"

namespace Gs2::Identifier::Result
{
    class GS2IDENTIFIER_API FGetPasswordResult final : public TSharedFromThis<FGetPasswordResult>
    {
        TSharedPtr<Model::FPassword> ItemValue;
        
    public:
        
        FGetPasswordResult();
        FGetPasswordResult(
            const FGetPasswordResult& From
        );
        ~FGetPasswordResult() = default;

        TSharedPtr<FGetPasswordResult> WithItem(const TSharedPtr<Model::FPassword> Item);

        TSharedPtr<Model::FPassword> GetItem() const;

        static TSharedPtr<FGetPasswordResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPasswordResult, ESPMode::ThreadSafe> FGetPasswordResultPtr;
}
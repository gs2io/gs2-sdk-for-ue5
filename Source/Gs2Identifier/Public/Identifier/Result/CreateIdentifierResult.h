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
#include "../Model/Identifier.h"

namespace Gs2::Identifier::Result
{
    class GS2IDENTIFIER_API FCreateIdentifierResult final : public TSharedFromThis<FCreateIdentifierResult>
    {
        TSharedPtr<Model::FIdentifier> ItemValue;
        TOptional<FString> ClientSecretValue;
        
    public:
        
        FCreateIdentifierResult();
        FCreateIdentifierResult(
            const FCreateIdentifierResult& From
        );
        ~FCreateIdentifierResult() = default;

        TSharedPtr<FCreateIdentifierResult> WithItem(const TSharedPtr<Model::FIdentifier> Item);
        TSharedPtr<FCreateIdentifierResult> WithClientSecret(const TOptional<FString> ClientSecret);

        TSharedPtr<Model::FIdentifier> GetItem() const;
        TOptional<FString> GetClientSecret() const;

        static TSharedPtr<FCreateIdentifierResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateIdentifierResult, ESPMode::ThreadSafe> FCreateIdentifierResultPtr;
}
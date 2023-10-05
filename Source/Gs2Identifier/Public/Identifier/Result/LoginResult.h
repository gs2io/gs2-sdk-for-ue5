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

namespace Gs2::Identifier::Result
{
    class GS2IDENTIFIER_API FLoginResult final : public TSharedFromThis<FLoginResult>
    {
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TokenTypeValue;
        TOptional<int32> ExpiresInValue;
        TOptional<FString> OwnerIdValue;
        
    public:
        
        FLoginResult();
        FLoginResult(
            const FLoginResult& From
        );
        ~FLoginResult() = default;

        TSharedPtr<FLoginResult> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FLoginResult> WithTokenType(const TOptional<FString> TokenType);
        TSharedPtr<FLoginResult> WithExpiresIn(const TOptional<int32> ExpiresIn);
        TSharedPtr<FLoginResult> WithOwnerId(const TOptional<FString> OwnerId);

        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTokenType() const;
        TOptional<int32> GetExpiresIn() const;
        FString GetExpiresInString() const;
        TOptional<FString> GetOwnerId() const;

        static TSharedPtr<FLoginResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLoginResult, ESPMode::ThreadSafe> FLoginResultPtr;
}
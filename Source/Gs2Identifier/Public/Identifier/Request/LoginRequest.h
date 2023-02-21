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

namespace Gs2::Identifier::Request
{
    class FLoginRequest;

    class GS2IDENTIFIER_API FLoginRequest final : public TSharedFromThis<FLoginRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> ClientIdValue;
        TOptional<FString> ClientSecretValue;
        
    public:
        
        FLoginRequest();
        FLoginRequest(
            const FLoginRequest& From
        );
        ~FLoginRequest() = default;

        TSharedPtr<FLoginRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FLoginRequest> WithClientId(const TOptional<FString> ClientId);
        TSharedPtr<FLoginRequest> WithClientSecret(const TOptional<FString> ClientSecret);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetClientId() const;
        TOptional<FString> GetClientSecret() const;

        static TSharedPtr<FLoginRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLoginRequest, ESPMode::ThreadSafe> FLoginRequestPtr;
}
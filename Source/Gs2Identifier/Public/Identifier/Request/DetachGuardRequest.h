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
#include "Dom/JsonObject.h"

namespace Gs2::Identifier::Request
{
    class FDetachGuardRequest;

    class GS2IDENTIFIER_API FDetachGuardRequest final : public TSharedFromThis<FDetachGuardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserNameValue;
        TOptional<FString> ClientIdValue;
        TOptional<FString> GuardNamespaceIdValue;
        
    public:
        
        FDetachGuardRequest();
        FDetachGuardRequest(
            const FDetachGuardRequest& From
        );
        ~FDetachGuardRequest() = default;

        TSharedPtr<FDetachGuardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDetachGuardRequest> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FDetachGuardRequest> WithClientId(const TOptional<FString> ClientId);
        TSharedPtr<FDetachGuardRequest> WithGuardNamespaceId(const TOptional<FString> GuardNamespaceId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserName() const;
        TOptional<FString> GetClientId() const;
        TOptional<FString> GetGuardNamespaceId() const;

        static TSharedPtr<FDetachGuardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDetachGuardRequest> FDetachGuardRequestPtr;
}
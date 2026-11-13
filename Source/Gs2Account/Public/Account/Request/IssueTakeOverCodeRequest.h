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

namespace Gs2::Account::Request
{
    class FIssueTakeOverCodeRequest;

    class GS2ACCOUNT_API FIssueTakeOverCodeRequest final : public TSharedFromThis<FIssueTakeOverCodeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> TypeValue;
        
    public:
        
        FIssueTakeOverCodeRequest();
        FIssueTakeOverCodeRequest(
            const FIssueTakeOverCodeRequest& From
        );
        ~FIssueTakeOverCodeRequest() = default;

        TSharedPtr<FIssueTakeOverCodeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIssueTakeOverCodeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIssueTakeOverCodeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FIssueTakeOverCodeRequest> WithType(const TOptional<int32> Type);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;

        static TSharedPtr<FIssueTakeOverCodeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIssueTakeOverCodeRequest> FIssueTakeOverCodeRequestPtr;
}
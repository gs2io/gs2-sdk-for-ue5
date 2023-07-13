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

namespace Gs2::LoginReward::Request
{
    class FGetReceiveStatusRequest;

    class GS2LOGINREWARD_API FGetReceiveStatusRequest final : public TSharedFromThis<FGetReceiveStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetReceiveStatusRequest();
        FGetReceiveStatusRequest(
            const FGetReceiveStatusRequest& From
        );
        ~FGetReceiveStatusRequest() = default;

        TSharedPtr<FGetReceiveStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetReceiveStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetReceiveStatusRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FGetReceiveStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetReceiveStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetReceiveStatusRequest, ESPMode::ThreadSafe> FGetReceiveStatusRequestPtr;
}
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
    class FGetReceiveStatusByUserIdRequest;

    class GS2LOGINREWARD_API FGetReceiveStatusByUserIdRequest final : public TSharedFromThis<FGetReceiveStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetReceiveStatusByUserIdRequest();
        FGetReceiveStatusByUserIdRequest(
            const FGetReceiveStatusByUserIdRequest& From
        );
        ~FGetReceiveStatusByUserIdRequest() = default;

        TSharedPtr<FGetReceiveStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetReceiveStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetReceiveStatusByUserIdRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FGetReceiveStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetReceiveStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetReceiveStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetReceiveStatusByUserIdRequest, ESPMode::ThreadSafe> FGetReceiveStatusByUserIdRequestPtr;
}
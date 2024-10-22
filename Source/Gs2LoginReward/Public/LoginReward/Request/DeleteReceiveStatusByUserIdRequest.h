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

namespace Gs2::LoginReward::Request
{
    class FDeleteReceiveStatusByUserIdRequest;

    class GS2LOGINREWARD_API FDeleteReceiveStatusByUserIdRequest final : public TSharedFromThis<FDeleteReceiveStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteReceiveStatusByUserIdRequest();
        FDeleteReceiveStatusByUserIdRequest(
            const FDeleteReceiveStatusByUserIdRequest& From
        );
        ~FDeleteReceiveStatusByUserIdRequest() = default;

        TSharedPtr<FDeleteReceiveStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteReceiveStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteReceiveStatusByUserIdRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FDeleteReceiveStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteReceiveStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteReceiveStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteReceiveStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteReceiveStatusByUserIdRequest> FDeleteReceiveStatusByUserIdRequestPtr;
}
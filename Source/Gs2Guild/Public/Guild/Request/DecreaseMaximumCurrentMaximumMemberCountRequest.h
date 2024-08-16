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

namespace Gs2::Guild::Request
{
    class FDecreaseMaximumCurrentMaximumMemberCountRequest;

    class GS2GUILD_API FDecreaseMaximumCurrentMaximumMemberCountRequest final : public TSharedFromThis<FDecreaseMaximumCurrentMaximumMemberCountRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> ValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseMaximumCurrentMaximumMemberCountRequest();
        FDecreaseMaximumCurrentMaximumMemberCountRequest(
            const FDecreaseMaximumCurrentMaximumMemberCountRequest& From
        );
        ~FDecreaseMaximumCurrentMaximumMemberCountRequest() = default;

        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> WithValue(const TOptional<int32> Value);
        TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaximumCurrentMaximumMemberCountRequest> FDecreaseMaximumCurrentMaximumMemberCountRequestPtr;
}
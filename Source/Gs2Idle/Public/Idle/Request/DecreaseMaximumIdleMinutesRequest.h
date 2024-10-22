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

namespace Gs2::Idle::Request
{
    class FDecreaseMaximumIdleMinutesRequest;

    class GS2IDLE_API FDecreaseMaximumIdleMinutesRequest final : public TSharedFromThis<FDecreaseMaximumIdleMinutesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CategoryNameValue;
        TOptional<int32> DecreaseMinutesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseMaximumIdleMinutesRequest();
        FDecreaseMaximumIdleMinutesRequest(
            const FDecreaseMaximumIdleMinutesRequest& From
        );
        ~FDecreaseMaximumIdleMinutesRequest() = default;

        TSharedPtr<FDecreaseMaximumIdleMinutesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseMaximumIdleMinutesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseMaximumIdleMinutesRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDecreaseMaximumIdleMinutesRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDecreaseMaximumIdleMinutesRequest> WithDecreaseMinutes(const TOptional<int32> DecreaseMinutes);
        TSharedPtr<FDecreaseMaximumIdleMinutesRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<int32> GetDecreaseMinutes() const;
        FString GetDecreaseMinutesString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseMaximumIdleMinutesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaximumIdleMinutesRequest> FDecreaseMaximumIdleMinutesRequestPtr;
}
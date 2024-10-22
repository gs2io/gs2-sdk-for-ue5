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
    class FDecreaseMaximumIdleMinutesByUserIdRequest;

    class GS2IDLE_API FDecreaseMaximumIdleMinutesByUserIdRequest final : public TSharedFromThis<FDecreaseMaximumIdleMinutesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<int32> DecreaseMinutesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDecreaseMaximumIdleMinutesByUserIdRequest();
        FDecreaseMaximumIdleMinutesByUserIdRequest(
            const FDecreaseMaximumIdleMinutesByUserIdRequest& From
        );
        ~FDecreaseMaximumIdleMinutesByUserIdRequest() = default;

        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithDecreaseMinutes(const TOptional<int32> DecreaseMinutes);
        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<int32> GetDecreaseMinutes() const;
        FString GetDecreaseMinutesString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequestPtr;
}
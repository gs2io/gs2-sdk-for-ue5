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

namespace Gs2::Idle::Request
{
    class FIncreaseMaximumIdleMinutesByUserIdRequest;

    class GS2IDLE_API FIncreaseMaximumIdleMinutesByUserIdRequest final : public TSharedFromThis<FIncreaseMaximumIdleMinutesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<int32> IncreaseMinutesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FIncreaseMaximumIdleMinutesByUserIdRequest();
        FIncreaseMaximumIdleMinutesByUserIdRequest(
            const FIncreaseMaximumIdleMinutesByUserIdRequest& From
        );
        ~FIncreaseMaximumIdleMinutesByUserIdRequest() = default;

        TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> WithIncreaseMinutes(const TOptional<int32> IncreaseMinutes);
        TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<int32> GetIncreaseMinutes() const;
        FString GetIncreaseMinutesString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest, ESPMode::ThreadSafe> FIncreaseMaximumIdleMinutesByUserIdRequestPtr;
}
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
    class FSetMaximumIdleMinutesByUserIdRequest;

    class GS2IDLE_API FSetMaximumIdleMinutesByUserIdRequest final : public TSharedFromThis<FSetMaximumIdleMinutesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<int32> MaximumIdleMinutesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetMaximumIdleMinutesByUserIdRequest();
        FSetMaximumIdleMinutesByUserIdRequest(
            const FSetMaximumIdleMinutesByUserIdRequest& From
        );
        ~FSetMaximumIdleMinutesByUserIdRequest() = default;

        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithMaximumIdleMinutes(const TOptional<int32> MaximumIdleMinutes);
        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<int32> GetMaximumIdleMinutes() const;
        FString GetMaximumIdleMinutesString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetMaximumIdleMinutesByUserIdRequest> FSetMaximumIdleMinutesByUserIdRequestPtr;
}
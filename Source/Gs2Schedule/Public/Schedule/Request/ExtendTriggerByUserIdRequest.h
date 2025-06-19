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

namespace Gs2::Schedule::Request
{
    class FExtendTriggerByUserIdRequest;

    class GS2SCHEDULE_API FExtendTriggerByUserIdRequest final : public TSharedFromThis<FExtendTriggerByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> TriggerNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> ExtendSecondsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FExtendTriggerByUserIdRequest();
        FExtendTriggerByUserIdRequest(
            const FExtendTriggerByUserIdRequest& From
        );
        ~FExtendTriggerByUserIdRequest() = default;

        TSharedPtr<FExtendTriggerByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FExtendTriggerByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FExtendTriggerByUserIdRequest> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FExtendTriggerByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FExtendTriggerByUserIdRequest> WithExtendSeconds(const TOptional<int32> ExtendSeconds);
        TSharedPtr<FExtendTriggerByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FExtendTriggerByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetTriggerName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetExtendSeconds() const;
        FString GetExtendSecondsString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FExtendTriggerByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExtendTriggerByUserIdRequest> FExtendTriggerByUserIdRequestPtr;
}
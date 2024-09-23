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

namespace Gs2::Schedule::Request
{
    class FVerifyTriggerByUserIdRequest;

    class GS2SCHEDULE_API FVerifyTriggerByUserIdRequest final : public TSharedFromThis<FVerifyTriggerByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TriggerNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> ElapsedMinutesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyTriggerByUserIdRequest();
        FVerifyTriggerByUserIdRequest(
            const FVerifyTriggerByUserIdRequest& From
        );
        ~FVerifyTriggerByUserIdRequest() = default;

        TSharedPtr<FVerifyTriggerByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithElapsedMinutes(const TOptional<int32> ElapsedMinutes);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyTriggerByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTriggerName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetElapsedMinutes() const;
        FString GetElapsedMinutesString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyTriggerByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyTriggerByUserIdRequest, ESPMode::ThreadSafe> FVerifyTriggerByUserIdRequestPtr;
}
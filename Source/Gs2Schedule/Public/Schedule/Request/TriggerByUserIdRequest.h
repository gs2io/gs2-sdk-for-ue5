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
    class FTriggerByUserIdRequest;

    class GS2SCHEDULE_API FTriggerByUserIdRequest final : public TSharedFromThis<FTriggerByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> TriggerNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TriggerStrategyValue;
        TOptional<int32> TtlValue;
        TOptional<FString> EventIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FTriggerByUserIdRequest();
        FTriggerByUserIdRequest(
            const FTriggerByUserIdRequest& From
        );
        ~FTriggerByUserIdRequest() = default;

        TSharedPtr<FTriggerByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FTriggerByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FTriggerByUserIdRequest> WithTriggerName(const TOptional<FString> TriggerName);
        TSharedPtr<FTriggerByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FTriggerByUserIdRequest> WithTriggerStrategy(const TOptional<FString> TriggerStrategy);
        TSharedPtr<FTriggerByUserIdRequest> WithTtl(const TOptional<int32> Ttl);
        TSharedPtr<FTriggerByUserIdRequest> WithEventId(const TOptional<FString> EventId);
        TSharedPtr<FTriggerByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FTriggerByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetTriggerName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTriggerStrategy() const;
        TOptional<int32> GetTtl() const;
        FString GetTtlString() const;
        TOptional<FString> GetEventId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FTriggerByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequestPtr;
}
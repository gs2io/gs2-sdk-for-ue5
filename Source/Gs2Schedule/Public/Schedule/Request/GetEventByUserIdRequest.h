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
    class FGetEventByUserIdRequest;

    class GS2SCHEDULE_API FGetEventByUserIdRequest final : public TSharedFromThis<FGetEventByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> EventNameValue;
        TOptional<FString> UserIdValue;
        TOptional<bool> IsInScheduleValue;
        
    public:
        
        FGetEventByUserIdRequest();
        FGetEventByUserIdRequest(
            const FGetEventByUserIdRequest& From
        );
        ~FGetEventByUserIdRequest() = default;

        TSharedPtr<FGetEventByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetEventByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetEventByUserIdRequest> WithEventName(const TOptional<FString> EventName);
        TSharedPtr<FGetEventByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetEventByUserIdRequest> WithIsInSchedule(const TOptional<bool> IsInSchedule);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetEventName() const;
        TOptional<FString> GetUserId() const;
        TOptional<bool> GetIsInSchedule() const;
        FString GetIsInScheduleString() const;

        static TSharedPtr<FGetEventByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEventByUserIdRequest, ESPMode::ThreadSafe> FGetEventByUserIdRequestPtr;
}
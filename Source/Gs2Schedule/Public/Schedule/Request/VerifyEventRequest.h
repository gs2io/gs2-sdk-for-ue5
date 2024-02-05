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
    class FVerifyEventRequest;

    class GS2SCHEDULE_API FVerifyEventRequest final : public TSharedFromThis<FVerifyEventRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> EventNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyEventRequest();
        FVerifyEventRequest(
            const FVerifyEventRequest& From
        );
        ~FVerifyEventRequest() = default;

        TSharedPtr<FVerifyEventRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyEventRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyEventRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyEventRequest> WithEventName(const TOptional<FString> EventName);
        TSharedPtr<FVerifyEventRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyEventRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetEventName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyEventRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyEventRequest, ESPMode::ThreadSafe> FVerifyEventRequestPtr;
}
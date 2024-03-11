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
#include "../Model/Event.h"

namespace Gs2::StateMachine::Request
{
    class FReportByUserIdRequest;

    class GS2STATEMACHINE_API FReportByUserIdRequest final : public TSharedFromThis<FReportByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> StatusNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> EventsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReportByUserIdRequest();
        FReportByUserIdRequest(
            const FReportByUserIdRequest& From
        );
        ~FReportByUserIdRequest() = default;

        TSharedPtr<FReportByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReportByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReportByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReportByUserIdRequest> WithStatusName(const TOptional<FString> StatusName);
        TSharedPtr<FReportByUserIdRequest> WithEvents(const TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> Events);
        TSharedPtr<FReportByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FReportByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetStatusName() const;TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> GetEvents() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReportByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReportByUserIdRequest, ESPMode::ThreadSafe> FReportByUserIdRequestPtr;
}
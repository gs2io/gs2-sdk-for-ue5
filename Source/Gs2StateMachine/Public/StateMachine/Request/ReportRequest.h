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
    class FReportRequest;

    class GS2STATEMACHINE_API FReportRequest final : public TSharedFromThis<FReportRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> StatusNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> EventsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReportRequest();
        FReportRequest(
            const FReportRequest& From
        );
        ~FReportRequest() = default;

        TSharedPtr<FReportRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReportRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReportRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FReportRequest> WithStatusName(const TOptional<FString> StatusName);
        TSharedPtr<FReportRequest> WithEvents(const TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> Events);
        TSharedPtr<FReportRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetStatusName() const;TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> GetEvents() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReportRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReportRequest, ESPMode::ThreadSafe> FReportRequestPtr;
}
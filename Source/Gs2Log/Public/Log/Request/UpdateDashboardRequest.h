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

namespace Gs2::Log::Request
{
    class FUpdateDashboardRequest;

    class GS2LOG_API FUpdateDashboardRequest final : public TSharedFromThis<FUpdateDashboardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DashboardNameValue;
        TOptional<FString> DisplayNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> PayloadValue;
        
    public:
        
        FUpdateDashboardRequest();
        FUpdateDashboardRequest(
            const FUpdateDashboardRequest& From
        );
        ~FUpdateDashboardRequest() = default;

        TSharedPtr<FUpdateDashboardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateDashboardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateDashboardRequest> WithDashboardName(const TOptional<FString> DashboardName);
        TSharedPtr<FUpdateDashboardRequest> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FUpdateDashboardRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateDashboardRequest> WithPayload(const TOptional<FString> Payload);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDashboardName() const;
        TOptional<FString> GetDisplayName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetPayload() const;

        static TSharedPtr<FUpdateDashboardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequestPtr;
}
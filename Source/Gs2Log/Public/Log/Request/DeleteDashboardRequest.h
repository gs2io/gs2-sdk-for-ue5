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
    class FDeleteDashboardRequest;

    class GS2LOG_API FDeleteDashboardRequest final : public TSharedFromThis<FDeleteDashboardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DashboardNameValue;
        
    public:
        
        FDeleteDashboardRequest();
        FDeleteDashboardRequest(
            const FDeleteDashboardRequest& From
        );
        ~FDeleteDashboardRequest() = default;

        TSharedPtr<FDeleteDashboardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteDashboardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteDashboardRequest> WithDashboardName(const TOptional<FString> DashboardName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDashboardName() const;

        static TSharedPtr<FDeleteDashboardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteDashboardRequest> FDeleteDashboardRequestPtr;
}
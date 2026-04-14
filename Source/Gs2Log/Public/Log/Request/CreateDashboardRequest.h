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
    class FCreateDashboardRequest;

    class GS2LOG_API FCreateDashboardRequest final : public TSharedFromThis<FCreateDashboardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DisplayNameValue;
        TOptional<FString> DescriptionValue;
        
    public:
        
        FCreateDashboardRequest();
        FCreateDashboardRequest(
            const FCreateDashboardRequest& From
        );
        ~FCreateDashboardRequest() = default;

        TSharedPtr<FCreateDashboardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateDashboardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateDashboardRequest> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FCreateDashboardRequest> WithDescription(const TOptional<FString> Description);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDisplayName() const;
        TOptional<FString> GetDescription() const;

        static TSharedPtr<FCreateDashboardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateDashboardRequest> FCreateDashboardRequestPtr;
}
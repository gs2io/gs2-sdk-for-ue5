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
#include "../Model/AcquireAction.h"
#include "../Model/Config.h"

namespace Gs2::Formation::Request
{
    class FAcquireActionsToPropertyFormPropertiesRequest;

    class GS2FORMATION_API FAcquireActionsToPropertyFormPropertiesRequest final : public TSharedFromThis<FAcquireActionsToPropertyFormPropertiesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<Model::FAcquireAction> AcquireActionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireActionsToPropertyFormPropertiesRequest();
        FAcquireActionsToPropertyFormPropertiesRequest(
            const FAcquireActionsToPropertyFormPropertiesRequest& From
        );
        ~FAcquireActionsToPropertyFormPropertiesRequest() = default;

        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithAcquireAction(const TSharedPtr<Model::FAcquireAction> AcquireAction);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<Model::FAcquireAction> GetAcquireAction() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireActionsToPropertyFormPropertiesRequest, ESPMode::ThreadSafe> FAcquireActionsToPropertyFormPropertiesRequestPtr;
}
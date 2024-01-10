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
    class FAcquireActionsToFormPropertiesRequest;

    class GS2FORMATION_API FAcquireActionsToFormPropertiesRequest final : public TSharedFromThis<FAcquireActionsToFormPropertiesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TSharedPtr<Model::FAcquireAction> AcquireActionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireActionsToFormPropertiesRequest();
        FAcquireActionsToFormPropertiesRequest(
            const FAcquireActionsToFormPropertiesRequest& From
        );
        ~FAcquireActionsToFormPropertiesRequest() = default;

        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithAcquireAction(const TSharedPtr<Model::FAcquireAction> AcquireAction);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FAcquireActionsToFormPropertiesRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TSharedPtr<Model::FAcquireAction> GetAcquireAction() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireActionsToFormPropertiesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireActionsToFormPropertiesRequest, ESPMode::ThreadSafe> FAcquireActionsToFormPropertiesRequestPtr;
}
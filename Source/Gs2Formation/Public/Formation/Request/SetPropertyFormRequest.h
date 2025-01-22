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
#include "../Model/Slot.h"

namespace Gs2::Formation::Request
{
    class FSetPropertyFormRequest;

    class GS2FORMATION_API FSetPropertyFormRequest final : public TSharedFromThis<FSetPropertyFormRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> SlotsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetPropertyFormRequest();
        FSetPropertyFormRequest(
            const FSetPropertyFormRequest& From
        );
        ~FSetPropertyFormRequest() = default;

        TSharedPtr<FSetPropertyFormRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetPropertyFormRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetPropertyFormRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetPropertyFormRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FSetPropertyFormRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetPropertyFormRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> Slots);
        TSharedPtr<FSetPropertyFormRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPropertyId() const;TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> GetSlots() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetPropertyFormRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetPropertyFormRequest> FSetPropertyFormRequestPtr;
}
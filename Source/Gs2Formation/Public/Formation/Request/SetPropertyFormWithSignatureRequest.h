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
#include "../Model/SlotWithSignature.h"

namespace Gs2::Formation::Request
{
    class FSetPropertyFormWithSignatureRequest;

    class GS2FORMATION_API FSetPropertyFormWithSignatureRequest final : public TSharedFromThis<FSetPropertyFormWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> FormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> SlotsValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetPropertyFormWithSignatureRequest();
        FSetPropertyFormWithSignatureRequest(
            const FSetPropertyFormWithSignatureRequest& From
        );
        ~FSetPropertyFormWithSignatureRequest() = default;

        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> Slots);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FSetPropertyFormWithSignatureRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<FString> GetPropertyId() const;TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> GetSlots() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetPropertyFormWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetPropertyFormWithSignatureRequest, ESPMode::ThreadSafe> FSetPropertyFormWithSignatureRequestPtr;
}
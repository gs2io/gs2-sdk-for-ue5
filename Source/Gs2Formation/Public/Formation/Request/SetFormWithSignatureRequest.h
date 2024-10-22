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
#include "../Model/SlotWithSignature.h"

namespace Gs2::Formation::Request
{
    class FSetFormWithSignatureRequest;

    class GS2FORMATION_API FSetFormWithSignatureRequest final : public TSharedFromThis<FSetFormWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> SlotsValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetFormWithSignatureRequest();
        FSetFormWithSignatureRequest(
            const FSetFormWithSignatureRequest& From
        );
        ~FSetFormWithSignatureRequest() = default;

        TSharedPtr<FSetFormWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetFormWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetFormWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetFormWithSignatureRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FSetFormWithSignatureRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FSetFormWithSignatureRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> Slots);
        TSharedPtr<FSetFormWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FSetFormWithSignatureRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;TSharedPtr<TArray<TSharedPtr<Model::FSlotWithSignature>>> GetSlots() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetFormWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFormWithSignatureRequest> FSetFormWithSignatureRequestPtr;
}
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
    class FSetFormRequest;

    class GS2FORMATION_API FSetFormRequest final : public TSharedFromThis<FSetFormRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> SlotsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetFormRequest();
        FSetFormRequest(
            const FSetFormRequest& From
        );
        ~FSetFormRequest() = default;

        TSharedPtr<FSetFormRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetFormRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetFormRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSetFormRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FSetFormRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FSetFormRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> Slots);
        TSharedPtr<FSetFormRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> GetSlots() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetFormRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFormRequest> FSetFormRequestPtr;
}
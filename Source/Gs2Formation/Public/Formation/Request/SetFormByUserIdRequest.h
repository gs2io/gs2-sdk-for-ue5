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
#include "../Model/Slot.h"

namespace Gs2::Formation::Request
{
    class FSetFormByUserIdRequest;

    class GS2FORMATION_API FSetFormByUserIdRequest final : public TSharedFromThis<FSetFormByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> SlotsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetFormByUserIdRequest();
        FSetFormByUserIdRequest(
            const FSetFormByUserIdRequest& From
        );
        ~FSetFormByUserIdRequest() = default;

        TSharedPtr<FSetFormByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetFormByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetFormByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetFormByUserIdRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FSetFormByUserIdRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FSetFormByUserIdRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> Slots);
        TSharedPtr<FSetFormByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> GetSlots() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetFormByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetFormByUserIdRequest, ESPMode::ThreadSafe> FSetFormByUserIdRequestPtr;
}
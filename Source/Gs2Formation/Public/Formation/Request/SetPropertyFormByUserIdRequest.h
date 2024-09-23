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
    class FSetPropertyFormByUserIdRequest;

    class GS2FORMATION_API FSetPropertyFormByUserIdRequest final : public TSharedFromThis<FSetPropertyFormByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> SlotsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetPropertyFormByUserIdRequest();
        FSetPropertyFormByUserIdRequest(
            const FSetPropertyFormByUserIdRequest& From
        );
        ~FSetPropertyFormByUserIdRequest() = default;

        TSharedPtr<FSetPropertyFormByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> Slots);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetPropertyFormByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPropertyId() const;TSharedPtr<TArray<TSharedPtr<Model::FSlot>>> GetSlots() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetPropertyFormByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetPropertyFormByUserIdRequest, ESPMode::ThreadSafe> FSetPropertyFormByUserIdRequestPtr;
}
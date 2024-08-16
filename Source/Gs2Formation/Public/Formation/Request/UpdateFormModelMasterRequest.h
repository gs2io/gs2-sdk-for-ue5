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
#include "../Model/SlotModel.h"

namespace Gs2::Formation::Request
{
    class FUpdateFormModelMasterRequest;

    class GS2FORMATION_API FUpdateFormModelMasterRequest final : public TSharedFromThis<FUpdateFormModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> FormModelNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> SlotsValue;
        
    public:
        
        FUpdateFormModelMasterRequest();
        FUpdateFormModelMasterRequest(
            const FUpdateFormModelMasterRequest& From
        );
        ~FUpdateFormModelMasterRequest() = default;

        TSharedPtr<FUpdateFormModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateFormModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateFormModelMasterRequest> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FUpdateFormModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateFormModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateFormModelMasterRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> Slots);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> GetSlots() const;

        static TSharedPtr<FUpdateFormModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateFormModelMasterRequest> FUpdateFormModelMasterRequestPtr;
}
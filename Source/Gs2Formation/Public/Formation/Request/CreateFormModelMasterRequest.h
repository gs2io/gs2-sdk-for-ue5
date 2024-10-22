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
    class FCreateFormModelMasterRequest;

    class GS2FORMATION_API FCreateFormModelMasterRequest final : public TSharedFromThis<FCreateFormModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> SlotsValue;
        
    public:
        
        FCreateFormModelMasterRequest();
        FCreateFormModelMasterRequest(
            const FCreateFormModelMasterRequest& From
        );
        ~FCreateFormModelMasterRequest() = default;

        TSharedPtr<FCreateFormModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateFormModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateFormModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateFormModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateFormModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateFormModelMasterRequest> WithSlots(const TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> Slots);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FSlotModel>>> GetSlots() const;

        static TSharedPtr<FCreateFormModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateFormModelMasterRequest> FCreateFormModelMasterRequestPtr;
}
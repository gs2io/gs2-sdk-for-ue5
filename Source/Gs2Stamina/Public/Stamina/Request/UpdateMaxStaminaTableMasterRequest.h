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

namespace Gs2::Stamina::Request
{
    class FUpdateMaxStaminaTableMasterRequest;

    class GS2STAMINA_API FUpdateMaxStaminaTableMasterRequest final : public TSharedFromThis<FUpdateMaxStaminaTableMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MaxStaminaTableNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<int32>> ValuesValue;
        
    public:
        
        FUpdateMaxStaminaTableMasterRequest();
        FUpdateMaxStaminaTableMasterRequest(
            const FUpdateMaxStaminaTableMasterRequest& From
        );
        ~FUpdateMaxStaminaTableMasterRequest() = default;

        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithMaxStaminaTableName(const TOptional<FString> MaxStaminaTableName);
        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FUpdateMaxStaminaTableMasterRequest> WithValues(
            const TSharedPtr<TArray<int32>> Values);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMaxStaminaTableName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<int32>> GetValues() const;

        static TSharedPtr<FUpdateMaxStaminaTableMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMaxStaminaTableMasterRequest> FUpdateMaxStaminaTableMasterRequestPtr;
}
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

namespace Gs2::Stamina::Request
{
    class FCreateRecoverIntervalTableMasterRequest;

    class GS2STAMINA_API FCreateRecoverIntervalTableMasterRequest final : public TSharedFromThis<FCreateRecoverIntervalTableMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<int32>> ValuesValue;
        
    public:
        
        FCreateRecoverIntervalTableMasterRequest();
        FCreateRecoverIntervalTableMasterRequest(
            const FCreateRecoverIntervalTableMasterRequest& From
        );
        ~FCreateRecoverIntervalTableMasterRequest() = default;

        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FCreateRecoverIntervalTableMasterRequest> WithValues(
            const TSharedPtr<TArray<int32>> Values);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<int32>> GetValues() const;

        static TSharedPtr<FCreateRecoverIntervalTableMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRecoverIntervalTableMasterRequest, ESPMode::ThreadSafe> FCreateRecoverIntervalTableMasterRequestPtr;
}
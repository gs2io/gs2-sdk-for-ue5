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

namespace Gs2::Experience::Request
{
    class FUpdateThresholdMasterRequest;

    class GS2EXPERIENCE_API FUpdateThresholdMasterRequest final : public TSharedFromThis<FUpdateThresholdMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ThresholdNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<int64>> ValuesValue;
        
    public:
        
        FUpdateThresholdMasterRequest();
        FUpdateThresholdMasterRequest(
            const FUpdateThresholdMasterRequest& From
        );
        ~FUpdateThresholdMasterRequest() = default;

        TSharedPtr<FUpdateThresholdMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateThresholdMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateThresholdMasterRequest> WithThresholdName(const TOptional<FString> ThresholdName);
        TSharedPtr<FUpdateThresholdMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateThresholdMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateThresholdMasterRequest> WithValues(
            const TSharedPtr<TArray<int64>> Values);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetThresholdName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<int64>> GetValues() const;

        static TSharedPtr<FUpdateThresholdMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateThresholdMasterRequest> FUpdateThresholdMasterRequestPtr;
}
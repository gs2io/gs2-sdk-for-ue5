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

namespace Gs2::Formation::Request
{
    class FCreateMoldModelMasterRequest;

    class GS2FORMATION_API FCreateMoldModelMasterRequest final : public TSharedFromThis<FCreateMoldModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> FormModelNameValue;
        TOptional<int32> InitialMaxCapacityValue;
        TOptional<int32> MaxCapacityValue;
        
    public:
        
        FCreateMoldModelMasterRequest();
        FCreateMoldModelMasterRequest(
            const FCreateMoldModelMasterRequest& From
        );
        ~FCreateMoldModelMasterRequest() = default;

        TSharedPtr<FCreateMoldModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateMoldModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateMoldModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateMoldModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateMoldModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateMoldModelMasterRequest> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FCreateMoldModelMasterRequest> WithInitialMaxCapacity(const TOptional<int32> InitialMaxCapacity);
        TSharedPtr<FCreateMoldModelMasterRequest> WithMaxCapacity(const TOptional<int32> MaxCapacity);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<int32> GetInitialMaxCapacity() const;
        FString GetInitialMaxCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;

        static TSharedPtr<FCreateMoldModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateMoldModelMasterRequest, ESPMode::ThreadSafe> FCreateMoldModelMasterRequestPtr;
}
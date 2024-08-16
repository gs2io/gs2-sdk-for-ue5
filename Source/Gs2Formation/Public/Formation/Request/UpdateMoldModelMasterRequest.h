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

namespace Gs2::Formation::Request
{
    class FUpdateMoldModelMasterRequest;

    class GS2FORMATION_API FUpdateMoldModelMasterRequest final : public TSharedFromThis<FUpdateMoldModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> FormModelNameValue;
        TOptional<int32> InitialMaxCapacityValue;
        TOptional<int32> MaxCapacityValue;
        
    public:
        
        FUpdateMoldModelMasterRequest();
        FUpdateMoldModelMasterRequest(
            const FUpdateMoldModelMasterRequest& From
        );
        ~FUpdateMoldModelMasterRequest() = default;

        TSharedPtr<FUpdateMoldModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithInitialMaxCapacity(const TOptional<int32> InitialMaxCapacity);
        TSharedPtr<FUpdateMoldModelMasterRequest> WithMaxCapacity(const TOptional<int32> MaxCapacity);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<int32> GetInitialMaxCapacity() const;
        FString GetInitialMaxCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;

        static TSharedPtr<FUpdateMoldModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMoldModelMasterRequest> FUpdateMoldModelMasterRequestPtr;
}
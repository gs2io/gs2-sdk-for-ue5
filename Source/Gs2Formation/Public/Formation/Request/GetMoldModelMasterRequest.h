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
    class FGetMoldModelMasterRequest;

    class GS2FORMATION_API FGetMoldModelMasterRequest final : public TSharedFromThis<FGetMoldModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MoldModelNameValue;
        
    public:
        
        FGetMoldModelMasterRequest();
        FGetMoldModelMasterRequest(
            const FGetMoldModelMasterRequest& From
        );
        ~FGetMoldModelMasterRequest() = default;

        TSharedPtr<FGetMoldModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMoldModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMoldModelMasterRequest> WithMoldModelName(const TOptional<FString> MoldModelName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMoldModelName() const;

        static TSharedPtr<FGetMoldModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMoldModelMasterRequest, ESPMode::ThreadSafe> FGetMoldModelMasterRequestPtr;
}
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

namespace Gs2::Distributor::Request
{
    class FGetCurrentDistributorMasterRequest;

    class GS2DISTRIBUTOR_API FGetCurrentDistributorMasterRequest final : public TSharedFromThis<FGetCurrentDistributorMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        
    public:
        
        FGetCurrentDistributorMasterRequest();
        FGetCurrentDistributorMasterRequest(
            const FGetCurrentDistributorMasterRequest& From
        );
        ~FGetCurrentDistributorMasterRequest() = default;

        TSharedPtr<FGetCurrentDistributorMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCurrentDistributorMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;

        static TSharedPtr<FGetCurrentDistributorMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCurrentDistributorMasterRequest, ESPMode::ThreadSafe> FGetCurrentDistributorMasterRequestPtr;
}
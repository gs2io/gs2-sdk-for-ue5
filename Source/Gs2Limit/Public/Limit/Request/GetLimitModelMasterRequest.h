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

namespace Gs2::Limit::Request
{
    class FGetLimitModelMasterRequest;

    class GS2LIMIT_API FGetLimitModelMasterRequest final : public TSharedFromThis<FGetLimitModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> LimitNameValue;
        
    public:
        
        FGetLimitModelMasterRequest();
        FGetLimitModelMasterRequest(
            const FGetLimitModelMasterRequest& From
        );
        ~FGetLimitModelMasterRequest() = default;

        TSharedPtr<FGetLimitModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetLimitModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetLimitModelMasterRequest> WithLimitName(const TOptional<FString> LimitName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetLimitName() const;

        static TSharedPtr<FGetLimitModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetLimitModelMasterRequest, ESPMode::ThreadSafe> FGetLimitModelMasterRequestPtr;
}
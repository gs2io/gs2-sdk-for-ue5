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

namespace Gs2::Exchange::Request
{
    class FGetIncrementalRateModelMasterRequest;

    class GS2EXCHANGE_API FGetIncrementalRateModelMasterRequest final : public TSharedFromThis<FGetIncrementalRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        
    public:
        
        FGetIncrementalRateModelMasterRequest();
        FGetIncrementalRateModelMasterRequest(
            const FGetIncrementalRateModelMasterRequest& From
        );
        ~FGetIncrementalRateModelMasterRequest() = default;

        TSharedPtr<FGetIncrementalRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetIncrementalRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetIncrementalRateModelMasterRequest> WithRateName(const TOptional<FString> RateName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;

        static TSharedPtr<FGetIncrementalRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetIncrementalRateModelMasterRequest> FGetIncrementalRateModelMasterRequestPtr;
}
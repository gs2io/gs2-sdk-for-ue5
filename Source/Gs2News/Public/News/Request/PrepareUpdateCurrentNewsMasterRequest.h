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

namespace Gs2::News::Request
{
    class FPrepareUpdateCurrentNewsMasterRequest;

    class GS2NEWS_API FPrepareUpdateCurrentNewsMasterRequest final : public TSharedFromThis<FPrepareUpdateCurrentNewsMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        
    public:
        
        FPrepareUpdateCurrentNewsMasterRequest();
        FPrepareUpdateCurrentNewsMasterRequest(
            const FPrepareUpdateCurrentNewsMasterRequest& From
        );
        ~FPrepareUpdateCurrentNewsMasterRequest() = default;

        TSharedPtr<FPrepareUpdateCurrentNewsMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareUpdateCurrentNewsMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;

        static TSharedPtr<FPrepareUpdateCurrentNewsMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareUpdateCurrentNewsMasterRequest> FPrepareUpdateCurrentNewsMasterRequestPtr;
}
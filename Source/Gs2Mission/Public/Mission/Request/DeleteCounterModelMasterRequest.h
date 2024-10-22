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

namespace Gs2::Mission::Request
{
    class FDeleteCounterModelMasterRequest;

    class GS2MISSION_API FDeleteCounterModelMasterRequest final : public TSharedFromThis<FDeleteCounterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        
    public:
        
        FDeleteCounterModelMasterRequest();
        FDeleteCounterModelMasterRequest(
            const FDeleteCounterModelMasterRequest& From
        );
        ~FDeleteCounterModelMasterRequest() = default;

        TSharedPtr<FDeleteCounterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteCounterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteCounterModelMasterRequest> WithCounterName(const TOptional<FString> CounterName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;

        static TSharedPtr<FDeleteCounterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteCounterModelMasterRequest> FDeleteCounterModelMasterRequestPtr;
}
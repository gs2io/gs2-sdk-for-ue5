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

namespace Gs2::Deploy::Request
{
    class FPreChangeSetRequest;

    class GS2DEPLOY_API FPreChangeSetRequest final : public TSharedFromThis<FPreChangeSetRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        
    public:
        
        FPreChangeSetRequest();
        FPreChangeSetRequest(
            const FPreChangeSetRequest& From
        );
        ~FPreChangeSetRequest() = default;

        TSharedPtr<FPreChangeSetRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPreChangeSetRequest> WithStackName(const TOptional<FString> StackName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;

        static TSharedPtr<FPreChangeSetRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPreChangeSetRequest> FPreChangeSetRequestPtr;
}
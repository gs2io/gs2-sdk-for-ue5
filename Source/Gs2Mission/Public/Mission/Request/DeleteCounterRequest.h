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
    class FDeleteCounterRequest;

    class GS2MISSION_API FDeleteCounterRequest final : public TSharedFromThis<FDeleteCounterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteCounterRequest();
        FDeleteCounterRequest(
            const FDeleteCounterRequest& From
        );
        ~FDeleteCounterRequest() = default;

        TSharedPtr<FDeleteCounterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteCounterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteCounterRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeleteCounterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FDeleteCounterRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteCounterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteCounterRequest> FDeleteCounterRequestPtr;
}
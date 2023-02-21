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
    class FDeletePropertyFormRequest;

    class GS2FORMATION_API FDeletePropertyFormRequest final : public TSharedFromThis<FDeletePropertyFormRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> FormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeletePropertyFormRequest();
        FDeletePropertyFormRequest(
            const FDeletePropertyFormRequest& From
        );
        ~FDeletePropertyFormRequest() = default;

        TSharedPtr<FDeletePropertyFormRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeletePropertyFormRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeletePropertyFormRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDeletePropertyFormRequest> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FDeletePropertyFormRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FDeletePropertyFormRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeletePropertyFormRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeletePropertyFormRequest, ESPMode::ThreadSafe> FDeletePropertyFormRequestPtr;
}
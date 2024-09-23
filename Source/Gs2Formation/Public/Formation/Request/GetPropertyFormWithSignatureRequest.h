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
    class FGetPropertyFormWithSignatureRequest;

    class GS2FORMATION_API FGetPropertyFormWithSignatureRequest final : public TSharedFromThis<FGetPropertyFormWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PropertyFormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetPropertyFormWithSignatureRequest();
        FGetPropertyFormWithSignatureRequest(
            const FGetPropertyFormWithSignatureRequest& From
        );
        ~FGetPropertyFormWithSignatureRequest() = default;

        TSharedPtr<FGetPropertyFormWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPropertyFormWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPropertyFormWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetPropertyFormWithSignatureRequest> WithPropertyFormModelName(const TOptional<FString> PropertyFormModelName);
        TSharedPtr<FGetPropertyFormWithSignatureRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FGetPropertyFormWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPropertyFormModelName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetPropertyFormWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPropertyFormWithSignatureRequest, ESPMode::ThreadSafe> FGetPropertyFormWithSignatureRequestPtr;
}
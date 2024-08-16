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

namespace Gs2::Experience::Request
{
    class FGetStatusWithSignatureRequest;

    class GS2EXPERIENCE_API FGetStatusWithSignatureRequest final : public TSharedFromThis<FGetStatusWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetStatusWithSignatureRequest();
        FGetStatusWithSignatureRequest(
            const FGetStatusWithSignatureRequest& From
        );
        ~FGetStatusWithSignatureRequest() = default;

        TSharedPtr<FGetStatusWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStatusWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStatusWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetStatusWithSignatureRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FGetStatusWithSignatureRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FGetStatusWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetStatusWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStatusWithSignatureRequest> FGetStatusWithSignatureRequestPtr;
}
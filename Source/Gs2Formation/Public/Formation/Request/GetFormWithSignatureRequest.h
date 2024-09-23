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
    class FGetFormWithSignatureRequest;

    class GS2FORMATION_API FGetFormWithSignatureRequest final : public TSharedFromThis<FGetFormWithSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetFormWithSignatureRequest();
        FGetFormWithSignatureRequest(
            const FGetFormWithSignatureRequest& From
        );
        ~FGetFormWithSignatureRequest() = default;

        TSharedPtr<FGetFormWithSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFormWithSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFormWithSignatureRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetFormWithSignatureRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FGetFormWithSignatureRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FGetFormWithSignatureRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetFormWithSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFormWithSignatureRequest, ESPMode::ThreadSafe> FGetFormWithSignatureRequestPtr;
}
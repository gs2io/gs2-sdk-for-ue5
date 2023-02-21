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
    class FGetPropertyFormWithSignatureByUserIdRequest;

    class GS2FORMATION_API FGetPropertyFormWithSignatureByUserIdRequest final : public TSharedFromThis<FGetPropertyFormWithSignatureByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> FormModelNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetPropertyFormWithSignatureByUserIdRequest();
        FGetPropertyFormWithSignatureByUserIdRequest(
            const FGetPropertyFormWithSignatureByUserIdRequest& From
        );
        ~FGetPropertyFormWithSignatureByUserIdRequest() = default;

        TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPropertyFormWithSignatureByUserIdRequest, ESPMode::ThreadSafe> FGetPropertyFormWithSignatureByUserIdRequestPtr;
}
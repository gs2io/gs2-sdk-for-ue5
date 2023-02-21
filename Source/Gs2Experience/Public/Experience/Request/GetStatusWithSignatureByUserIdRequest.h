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

namespace Gs2::Experience::Request
{
    class FGetStatusWithSignatureByUserIdRequest;

    class GS2EXPERIENCE_API FGetStatusWithSignatureByUserIdRequest final : public TSharedFromThis<FGetStatusWithSignatureByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetStatusWithSignatureByUserIdRequest();
        FGetStatusWithSignatureByUserIdRequest(
            const FGetStatusWithSignatureByUserIdRequest& From
        );
        ~FGetStatusWithSignatureByUserIdRequest() = default;

        TSharedPtr<FGetStatusWithSignatureByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStatusWithSignatureByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStatusWithSignatureByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetStatusWithSignatureByUserIdRequest> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FGetStatusWithSignatureByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FGetStatusWithSignatureByUserIdRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetStatusWithSignatureByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStatusWithSignatureByUserIdRequest, ESPMode::ThreadSafe> FGetStatusWithSignatureByUserIdRequestPtr;
}
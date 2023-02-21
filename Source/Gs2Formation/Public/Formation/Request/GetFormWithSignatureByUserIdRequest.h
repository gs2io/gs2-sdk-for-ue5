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
    class FGetFormWithSignatureByUserIdRequest;

    class GS2FORMATION_API FGetFormWithSignatureByUserIdRequest final : public TSharedFromThis<FGetFormWithSignatureByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldNameValue;
        TOptional<int32> IndexValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FGetFormWithSignatureByUserIdRequest();
        FGetFormWithSignatureByUserIdRequest(
            const FGetFormWithSignatureByUserIdRequest& From
        );
        ~FGetFormWithSignatureByUserIdRequest() = default;

        TSharedPtr<FGetFormWithSignatureByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFormWithSignatureByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFormWithSignatureByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetFormWithSignatureByUserIdRequest> WithMoldName(const TOptional<FString> MoldName);
        TSharedPtr<FGetFormWithSignatureByUserIdRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FGetFormWithSignatureByUserIdRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FGetFormWithSignatureByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFormWithSignatureByUserIdRequest, ESPMode::ThreadSafe> FGetFormWithSignatureByUserIdRequestPtr;
}
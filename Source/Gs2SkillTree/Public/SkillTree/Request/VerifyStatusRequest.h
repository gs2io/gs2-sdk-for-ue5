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

namespace Gs2::SkillTree::Request
{
    class FVerifyStatusRequest;

    class GS2SKILLTREE_API FVerifyStatusRequest final : public TSharedFromThis<FVerifyStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> NodeModelNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyStatusRequest();
        FVerifyStatusRequest(
            const FVerifyStatusRequest& From
        );
        ~FVerifyStatusRequest() = default;

        TSharedPtr<FVerifyStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyStatusRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyStatusRequest> WithNodeModelName(const TOptional<FString> NodeModelName);
        TSharedPtr<FVerifyStatusRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyStatusRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetNodeModelName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyStatusRequest> FVerifyStatusRequestPtr;
}
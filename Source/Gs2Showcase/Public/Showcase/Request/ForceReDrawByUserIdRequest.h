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

namespace Gs2::Showcase::Request
{
    class FForceReDrawByUserIdRequest;

    class GS2SHOWCASE_API FForceReDrawByUserIdRequest final : public TSharedFromThis<FForceReDrawByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FForceReDrawByUserIdRequest();
        FForceReDrawByUserIdRequest(
            const FForceReDrawByUserIdRequest& From
        );
        ~FForceReDrawByUserIdRequest() = default;

        TSharedPtr<FForceReDrawByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FForceReDrawByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FForceReDrawByUserIdRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FForceReDrawByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FForceReDrawByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FForceReDrawByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FForceReDrawByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FForceReDrawByUserIdRequest> FForceReDrawByUserIdRequestPtr;
}
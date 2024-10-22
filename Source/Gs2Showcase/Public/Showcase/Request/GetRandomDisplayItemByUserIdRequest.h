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
    class FGetRandomDisplayItemByUserIdRequest;

    class GS2SHOWCASE_API FGetRandomDisplayItemByUserIdRequest final : public TSharedFromThis<FGetRandomDisplayItemByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetRandomDisplayItemByUserIdRequest();
        FGetRandomDisplayItemByUserIdRequest(
            const FGetRandomDisplayItemByUserIdRequest& From
        );
        ~FGetRandomDisplayItemByUserIdRequest() = default;

        TSharedPtr<FGetRandomDisplayItemByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRandomDisplayItemByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRandomDisplayItemByUserIdRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FGetRandomDisplayItemByUserIdRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FGetRandomDisplayItemByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetRandomDisplayItemByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetRandomDisplayItemByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRandomDisplayItemByUserIdRequest> FGetRandomDisplayItemByUserIdRequestPtr;
}
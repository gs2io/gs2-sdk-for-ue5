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
#include "../Model/Config.h"

namespace Gs2::Showcase::Request
{
    class FRandomShowcaseBuyByUserIdRequest;

    class GS2SHOWCASE_API FRandomShowcaseBuyByUserIdRequest final : public TSharedFromThis<FRandomShowcaseBuyByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> QuantityValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRandomShowcaseBuyByUserIdRequest();
        FRandomShowcaseBuyByUserIdRequest(
            const FRandomShowcaseBuyByUserIdRequest& From
        );
        ~FRandomShowcaseBuyByUserIdRequest() = default;

        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithQuantity(const TOptional<int32> Quantity);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRandomShowcaseBuyByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetQuantity() const;
        FString GetQuantityString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRandomShowcaseBuyByUserIdRequest> FRandomShowcaseBuyByUserIdRequestPtr;
}
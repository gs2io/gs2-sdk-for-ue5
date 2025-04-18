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
    class FBuyByUserIdRequest;

    class GS2SHOWCASE_API FBuyByUserIdRequest final : public TSharedFromThis<FBuyByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemIdValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> QuantityValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBuyByUserIdRequest();
        FBuyByUserIdRequest(
            const FBuyByUserIdRequest& From
        );
        ~FBuyByUserIdRequest() = default;

        TSharedPtr<FBuyByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBuyByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBuyByUserIdRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FBuyByUserIdRequest> WithDisplayItemId(const TOptional<FString> DisplayItemId);
        TSharedPtr<FBuyByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBuyByUserIdRequest> WithQuantity(const TOptional<int32> Quantity);
        TSharedPtr<FBuyByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FBuyByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FBuyByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemId() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetQuantity() const;
        FString GetQuantityString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBuyByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBuyByUserIdRequest> FBuyByUserIdRequestPtr;
}
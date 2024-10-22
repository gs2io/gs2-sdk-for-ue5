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
    class FBuyRequest;

    class GS2SHOWCASE_API FBuyRequest final : public TSharedFromThis<FBuyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemIdValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> QuantityValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBuyRequest();
        FBuyRequest(
            const FBuyRequest& From
        );
        ~FBuyRequest() = default;

        TSharedPtr<FBuyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBuyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBuyRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FBuyRequest> WithDisplayItemId(const TOptional<FString> DisplayItemId);
        TSharedPtr<FBuyRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FBuyRequest> WithQuantity(const TOptional<int32> Quantity);
        TSharedPtr<FBuyRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FBuyRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemId() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetQuantity() const;
        FString GetQuantityString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBuyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBuyRequest> FBuyRequestPtr;
}
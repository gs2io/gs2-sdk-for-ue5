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
    class FRandomShowcaseBuyRequest;

    class GS2SHOWCASE_API FRandomShowcaseBuyRequest final : public TSharedFromThis<FRandomShowcaseBuyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> QuantityValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRandomShowcaseBuyRequest();
        FRandomShowcaseBuyRequest(
            const FRandomShowcaseBuyRequest& From
        );
        ~FRandomShowcaseBuyRequest() = default;

        TSharedPtr<FRandomShowcaseBuyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRandomShowcaseBuyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRandomShowcaseBuyRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FRandomShowcaseBuyRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FRandomShowcaseBuyRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FRandomShowcaseBuyRequest> WithQuantity(const TOptional<int32> Quantity);
        TSharedPtr<FRandomShowcaseBuyRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FRandomShowcaseBuyRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetQuantity() const;
        FString GetQuantityString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRandomShowcaseBuyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRandomShowcaseBuyRequest> FRandomShowcaseBuyRequestPtr;
}
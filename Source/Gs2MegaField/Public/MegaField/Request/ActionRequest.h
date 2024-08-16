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
#include "../Model/MyPosition.h"
#include "../Model/Scope.h"

namespace Gs2::MegaField::Request
{
    class FActionRequest;

    class GS2MEGAFIELD_API FActionRequest final : public TSharedFromThis<FActionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Model::FMyPosition> PositionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FScope>>> ScopesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FActionRequest();
        FActionRequest(
            const FActionRequest& From
        );
        ~FActionRequest() = default;

        TSharedPtr<FActionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FActionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FActionRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FActionRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FActionRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FActionRequest> WithPosition(const TSharedPtr<Model::FMyPosition> Position);
        TSharedPtr<FActionRequest> WithScopes(const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> Scopes);
        TSharedPtr<FActionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<Model::FMyPosition> GetPosition() const;TSharedPtr<TArray<TSharedPtr<Model::FScope>>> GetScopes() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FActionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FActionRequest> FActionRequestPtr;
}
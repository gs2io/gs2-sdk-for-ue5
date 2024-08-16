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
    class FActionByUserIdRequest;

    class GS2MEGAFIELD_API FActionByUserIdRequest final : public TSharedFromThis<FActionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Model::FMyPosition> PositionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FScope>>> ScopesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FActionByUserIdRequest();
        FActionByUserIdRequest(
            const FActionByUserIdRequest& From
        );
        ~FActionByUserIdRequest() = default;

        TSharedPtr<FActionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FActionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FActionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FActionByUserIdRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FActionByUserIdRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FActionByUserIdRequest> WithPosition(const TSharedPtr<Model::FMyPosition> Position);
        TSharedPtr<FActionByUserIdRequest> WithScopes(const TSharedPtr<TArray<TSharedPtr<Model::FScope>>> Scopes);
        TSharedPtr<FActionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FActionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<Model::FMyPosition> GetPosition() const;TSharedPtr<TArray<TSharedPtr<Model::FScope>>> GetScopes() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FActionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FActionByUserIdRequest> FActionByUserIdRequestPtr;
}
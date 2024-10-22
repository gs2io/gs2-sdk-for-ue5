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
#include "../Model/Position.h"

namespace Gs2::MegaField::Request
{
    class FNearUserIdsRequest;

    class GS2MEGAFIELD_API FNearUserIdsRequest final : public TSharedFromThis<FNearUserIdsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Model::FPosition> PointValue;
        TOptional<float> RValue;
        TOptional<int32> LimitValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FNearUserIdsRequest();
        FNearUserIdsRequest(
            const FNearUserIdsRequest& From
        );
        ~FNearUserIdsRequest() = default;

        TSharedPtr<FNearUserIdsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FNearUserIdsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FNearUserIdsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FNearUserIdsRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FNearUserIdsRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FNearUserIdsRequest> WithPoint(const TSharedPtr<Model::FPosition> Point);
        TSharedPtr<FNearUserIdsRequest> WithR(const TOptional<float> R);
        TSharedPtr<FNearUserIdsRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FNearUserIdsRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<Model::FPosition> GetPoint() const;
        TOptional<float> GetR() const;
        FString GetRString() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FNearUserIdsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequestPtr;
}
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
#include "../Model/Position.h"

namespace Gs2::MegaField::Request
{
    class FNearUserIdsFromSystemRequest;

    class GS2MEGAFIELD_API FNearUserIdsFromSystemRequest final : public TSharedFromThis<FNearUserIdsFromSystemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Model::FPosition> PointValue;
        TOptional<float> RValue;
        TOptional<int32> LimitValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FNearUserIdsFromSystemRequest();
        FNearUserIdsFromSystemRequest(
            const FNearUserIdsFromSystemRequest& From
        );
        ~FNearUserIdsFromSystemRequest() = default;

        TSharedPtr<FNearUserIdsFromSystemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithPoint(const TSharedPtr<Model::FPosition> Point);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithR(const TOptional<float> R);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FNearUserIdsFromSystemRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<Model::FPosition> GetPoint() const;
        TOptional<float> GetR() const;
        FString GetRString() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FNearUserIdsFromSystemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FNearUserIdsFromSystemRequest, ESPMode::ThreadSafe> FNearUserIdsFromSystemRequestPtr;
}
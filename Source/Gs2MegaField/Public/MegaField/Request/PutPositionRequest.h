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
#include "../Model/Vector.h"

namespace Gs2::MegaField::Request
{
    class FPutPositionRequest;

    class GS2MEGAFIELD_API FPutPositionRequest final : public TSharedFromThis<FPutPositionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Model::FPosition> PositionValue;
        TSharedPtr<Model::FVector> VectorValue;
        TOptional<float> RValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPutPositionRequest();
        FPutPositionRequest(
            const FPutPositionRequest& From
        );
        ~FPutPositionRequest() = default;

        TSharedPtr<FPutPositionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPutPositionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPutPositionRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPutPositionRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FPutPositionRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FPutPositionRequest> WithPosition(const TSharedPtr<Model::FPosition> Position);
        TSharedPtr<FPutPositionRequest> WithVector(const TSharedPtr<Model::FVector> Vector);
        TSharedPtr<FPutPositionRequest> WithR(const TOptional<float> R);
        TSharedPtr<FPutPositionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<Model::FPosition> GetPosition() const;
        TSharedPtr<Model::FVector> GetVector() const;
        TOptional<float> GetR() const;
        FString GetRString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPutPositionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutPositionRequest, ESPMode::ThreadSafe> FPutPositionRequestPtr;
}
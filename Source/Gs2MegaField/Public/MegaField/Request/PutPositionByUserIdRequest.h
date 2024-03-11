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
    class FPutPositionByUserIdRequest;

    class GS2MEGAFIELD_API FPutPositionByUserIdRequest final : public TSharedFromThis<FPutPositionByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Model::FPosition> PositionValue;
        TSharedPtr<Model::FVector> VectorValue;
        TOptional<float> RValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPutPositionByUserIdRequest();
        FPutPositionByUserIdRequest(
            const FPutPositionByUserIdRequest& From
        );
        ~FPutPositionByUserIdRequest() = default;

        TSharedPtr<FPutPositionByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPutPositionByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPutPositionByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPutPositionByUserIdRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FPutPositionByUserIdRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FPutPositionByUserIdRequest> WithPosition(const TSharedPtr<Model::FPosition> Position);
        TSharedPtr<FPutPositionByUserIdRequest> WithVector(const TSharedPtr<Model::FVector> Vector);
        TSharedPtr<FPutPositionByUserIdRequest> WithR(const TOptional<float> R);
        TSharedPtr<FPutPositionByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPutPositionByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<Model::FPosition> GetPosition() const;
        TSharedPtr<Model::FVector> GetVector() const;
        TOptional<float> GetR() const;
        FString GetRString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPutPositionByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutPositionByUserIdRequest, ESPMode::ThreadSafe> FPutPositionByUserIdRequestPtr;
}
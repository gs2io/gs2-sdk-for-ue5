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
#include "../Model/Material.h"

namespace Gs2::Enhance::Request
{
    class FCreateProgressByUserIdRequest;

    class GS2ENHANCE_API FCreateProgressByUserIdRequest final : public TSharedFromThis<FCreateProgressByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> TargetItemSetIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> MaterialsValue;
        TOptional<bool> ForceValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateProgressByUserIdRequest();
        FCreateProgressByUserIdRequest(
            const FCreateProgressByUserIdRequest& From
        );
        ~FCreateProgressByUserIdRequest() = default;

        TSharedPtr<FCreateProgressByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateProgressByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateProgressByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateProgressByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FCreateProgressByUserIdRequest> WithTargetItemSetId(const TOptional<FString> TargetItemSetId);
        TSharedPtr<FCreateProgressByUserIdRequest> WithMaterials(const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials);
        TSharedPtr<FCreateProgressByUserIdRequest> WithForce(const TOptional<bool> Force);
        TSharedPtr<FCreateProgressByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateProgressByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetTargetItemSetId() const;TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> GetMaterials() const;
        TOptional<bool> GetForce() const;
        FString GetForceString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateProgressByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateProgressByUserIdRequest, ESPMode::ThreadSafe> FCreateProgressByUserIdRequestPtr;
}
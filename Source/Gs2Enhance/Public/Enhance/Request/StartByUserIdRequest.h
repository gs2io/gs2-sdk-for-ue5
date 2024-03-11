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
#include "../Model/Config.h"

namespace Gs2::Enhance::Request
{
    class FStartByUserIdRequest;

    class GS2ENHANCE_API FStartByUserIdRequest final : public TSharedFromThis<FStartByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> TargetItemSetIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> MaterialsValue;
        TOptional<FString> UserIdValue;
        TOptional<bool> ForceValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FStartByUserIdRequest();
        FStartByUserIdRequest(
            const FStartByUserIdRequest& From
        );
        ~FStartByUserIdRequest() = default;

        TSharedPtr<FStartByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FStartByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FStartByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FStartByUserIdRequest> WithTargetItemSetId(const TOptional<FString> TargetItemSetId);
        TSharedPtr<FStartByUserIdRequest> WithMaterials(const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials);
        TSharedPtr<FStartByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStartByUserIdRequest> WithForce(const TOptional<bool> Force);
        TSharedPtr<FStartByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FStartByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FStartByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetTargetItemSetId() const;TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> GetMaterials() const;
        TOptional<FString> GetUserId() const;
        TOptional<bool> GetForce() const;
        FString GetForceString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FStartByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FStartByUserIdRequest, ESPMode::ThreadSafe> FStartByUserIdRequestPtr;
}
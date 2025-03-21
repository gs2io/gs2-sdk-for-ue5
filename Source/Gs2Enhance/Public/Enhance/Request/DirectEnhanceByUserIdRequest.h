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
#include "../Model/Material.h"
#include "../Model/Config.h"

namespace Gs2::Enhance::Request
{
    class FDirectEnhanceByUserIdRequest;

    class GS2ENHANCE_API FDirectEnhanceByUserIdRequest final : public TSharedFromThis<FDirectEnhanceByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetItemSetIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> MaterialsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDirectEnhanceByUserIdRequest();
        FDirectEnhanceByUserIdRequest(
            const FDirectEnhanceByUserIdRequest& From
        );
        ~FDirectEnhanceByUserIdRequest() = default;

        TSharedPtr<FDirectEnhanceByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithTargetItemSetId(const TOptional<FString> TargetItemSetId);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithMaterials(const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDirectEnhanceByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetItemSetId() const;TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> GetMaterials() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDirectEnhanceByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDirectEnhanceByUserIdRequest> FDirectEnhanceByUserIdRequestPtr;
}
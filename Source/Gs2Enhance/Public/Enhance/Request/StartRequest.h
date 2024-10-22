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
    class FStartRequest;

    class GS2ENHANCE_API FStartRequest final : public TSharedFromThis<FStartRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> TargetItemSetIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> MaterialsValue;
        TOptional<FString> AccessTokenValue;
        TOptional<bool> ForceValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FStartRequest();
        FStartRequest(
            const FStartRequest& From
        );
        ~FStartRequest() = default;

        TSharedPtr<FStartRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FStartRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FStartRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FStartRequest> WithTargetItemSetId(const TOptional<FString> TargetItemSetId);
        TSharedPtr<FStartRequest> WithMaterials(const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials);
        TSharedPtr<FStartRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FStartRequest> WithForce(const TOptional<bool> Force);
        TSharedPtr<FStartRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FStartRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetTargetItemSetId() const;TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> GetMaterials() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<bool> GetForce() const;
        FString GetForceString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FStartRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FStartRequest> FStartRequestPtr;
}
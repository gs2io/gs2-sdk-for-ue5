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
#include "../Model/Config.h"

namespace Gs2::Enhance::Request
{
    class FUnleashRequest;

    class GS2ENHANCE_API FUnleashRequest final : public TSharedFromThis<FUnleashRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TargetItemSetIdValue;
        TSharedPtr<TArray<FString>> MaterialsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnleashRequest();
        FUnleashRequest(
            const FUnleashRequest& From
        );
        ~FUnleashRequest() = default;

        TSharedPtr<FUnleashRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnleashRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnleashRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FUnleashRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUnleashRequest> WithTargetItemSetId(const TOptional<FString> TargetItemSetId);
        TSharedPtr<FUnleashRequest> WithMaterials(
            const TSharedPtr<TArray<FString>> Materials);
        TSharedPtr<FUnleashRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FUnleashRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTargetItemSetId() const;
        TSharedPtr<TArray<FString>> GetMaterials() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnleashRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnleashRequest, ESPMode::ThreadSafe> FUnleashRequestPtr;
}
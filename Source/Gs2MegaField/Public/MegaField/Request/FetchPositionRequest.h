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

namespace Gs2::MegaField::Request
{
    class FFetchPositionRequest;

    class GS2MEGAFIELD_API FFetchPositionRequest final : public TSharedFromThis<FFetchPositionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<TArray<FString>> UserIdsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FFetchPositionRequest();
        FFetchPositionRequest(
            const FFetchPositionRequest& From
        );
        ~FFetchPositionRequest() = default;

        TSharedPtr<FFetchPositionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FFetchPositionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FFetchPositionRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FFetchPositionRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FFetchPositionRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FFetchPositionRequest> WithUserIds(
            const TSharedPtr<TArray<FString>> UserIds);
        TSharedPtr<FFetchPositionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<TArray<FString>> GetUserIds() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FFetchPositionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FFetchPositionRequest, ESPMode::ThreadSafe> FFetchPositionRequestPtr;
}
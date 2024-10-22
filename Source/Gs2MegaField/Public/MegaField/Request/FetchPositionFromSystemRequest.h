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

namespace Gs2::MegaField::Request
{
    class FFetchPositionFromSystemRequest;

    class GS2MEGAFIELD_API FFetchPositionFromSystemRequest final : public TSharedFromThis<FFetchPositionFromSystemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<TArray<FString>> UserIdsValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FFetchPositionFromSystemRequest();
        FFetchPositionFromSystemRequest(
            const FFetchPositionFromSystemRequest& From
        );
        ~FFetchPositionFromSystemRequest() = default;

        TSharedPtr<FFetchPositionFromSystemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FFetchPositionFromSystemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FFetchPositionFromSystemRequest> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FFetchPositionFromSystemRequest> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FFetchPositionFromSystemRequest> WithUserIds(
            const TSharedPtr<TArray<FString>> UserIds);
        TSharedPtr<FFetchPositionFromSystemRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAreaModelName() const;
        TOptional<FString> GetLayerModelName() const;
        TSharedPtr<TArray<FString>> GetUserIds() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FFetchPositionFromSystemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FFetchPositionFromSystemRequest> FFetchPositionFromSystemRequestPtr;
}
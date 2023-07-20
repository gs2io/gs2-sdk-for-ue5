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

namespace Gs2::Enchant::Request
{
    class FDeleteRarityParameterStatusByUserIdRequest;

    class GS2ENCHANT_API FDeleteRarityParameterStatusByUserIdRequest final : public TSharedFromThis<FDeleteRarityParameterStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteRarityParameterStatusByUserIdRequest();
        FDeleteRarityParameterStatusByUserIdRequest(
            const FDeleteRarityParameterStatusByUserIdRequest& From
        );
        ~FDeleteRarityParameterStatusByUserIdRequest() = default;

        TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteRarityParameterStatusByUserIdRequest, ESPMode::ThreadSafe> FDeleteRarityParameterStatusByUserIdRequestPtr;
}
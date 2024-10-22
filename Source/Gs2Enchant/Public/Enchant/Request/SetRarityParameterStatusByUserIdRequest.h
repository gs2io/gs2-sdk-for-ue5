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
#include "../Model/RarityParameterValue.h"

namespace Gs2::Enchant::Request
{
    class FSetRarityParameterStatusByUserIdRequest;

    class GS2ENCHANT_API FSetRarityParameterStatusByUserIdRequest final : public TSharedFromThis<FSetRarityParameterStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> ParameterValuesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetRarityParameterStatusByUserIdRequest();
        FSetRarityParameterStatusByUserIdRequest(
            const FSetRarityParameterStatusByUserIdRequest& From
        );
        ~FSetRarityParameterStatusByUserIdRequest() = default;

        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithParameterValues(const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> ParameterValues);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetRarityParameterStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValue>>> GetParameterValues() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRarityParameterStatusByUserIdRequest> FSetRarityParameterStatusByUserIdRequestPtr;
}
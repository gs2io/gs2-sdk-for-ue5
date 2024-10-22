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
#include "../Model/BalanceParameterValue.h"

namespace Gs2::Enchant::Request
{
    class FSetBalanceParameterStatusByUserIdRequest;

    class GS2ENCHANT_API FSetBalanceParameterStatusByUserIdRequest final : public TSharedFromThis<FSetBalanceParameterStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> ParameterValuesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetBalanceParameterStatusByUserIdRequest();
        FSetBalanceParameterStatusByUserIdRequest(
            const FSetBalanceParameterStatusByUserIdRequest& From
        );
        ~FSetBalanceParameterStatusByUserIdRequest() = default;

        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithParameterValues(const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> ParameterValues);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValue>>> GetParameterValues() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetBalanceParameterStatusByUserIdRequest> FSetBalanceParameterStatusByUserIdRequestPtr;
}
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
    class FVerifyRarityParameterStatusByUserIdRequest;

    class GS2ENCHANT_API FVerifyRarityParameterStatusByUserIdRequest final : public TSharedFromThis<FVerifyRarityParameterStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> ParameterValueNameValue;
        TOptional<int32> ParameterCountValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyRarityParameterStatusByUserIdRequest();
        FVerifyRarityParameterStatusByUserIdRequest(
            const FVerifyRarityParameterStatusByUserIdRequest& From
        );
        ~FVerifyRarityParameterStatusByUserIdRequest() = default;

        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithParameterValueName(const TOptional<FString> ParameterValueName);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithParameterCount(const TOptional<int32> ParameterCount);
        TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetParameterValueName() const;
        TOptional<int32> GetParameterCount() const;
        FString GetParameterCountString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRarityParameterStatusByUserIdRequest, ESPMode::ThreadSafe> FVerifyRarityParameterStatusByUserIdRequestPtr;
}
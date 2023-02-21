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

namespace Gs2::Stamina::Request
{
    class FRaiseMaxValueByUserIdRequest;

    class GS2STAMINA_API FRaiseMaxValueByUserIdRequest final : public TSharedFromThis<FRaiseMaxValueByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> RaiseValueValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRaiseMaxValueByUserIdRequest();
        FRaiseMaxValueByUserIdRequest(
            const FRaiseMaxValueByUserIdRequest& From
        );
        ~FRaiseMaxValueByUserIdRequest() = default;

        TSharedPtr<FRaiseMaxValueByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRaiseMaxValueByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRaiseMaxValueByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FRaiseMaxValueByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRaiseMaxValueByUserIdRequest> WithRaiseValue(const TOptional<int32> RaiseValue);
        TSharedPtr<FRaiseMaxValueByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetRaiseValue() const;
        FString GetRaiseValueString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRaiseMaxValueByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRaiseMaxValueByUserIdRequest, ESPMode::ThreadSafe> FRaiseMaxValueByUserIdRequestPtr;
}
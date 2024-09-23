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
    class FSetRecoverValueByUserIdRequest;

    class GS2STAMINA_API FSetRecoverValueByUserIdRequest final : public TSharedFromThis<FSetRecoverValueByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> RecoverValueValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetRecoverValueByUserIdRequest();
        FSetRecoverValueByUserIdRequest(
            const FSetRecoverValueByUserIdRequest& From
        );
        ~FSetRecoverValueByUserIdRequest() = default;

        TSharedPtr<FSetRecoverValueByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetRecoverValueByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetRecoverValueByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FSetRecoverValueByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetRecoverValueByUserIdRequest> WithRecoverValue(const TOptional<int32> RecoverValue);
        TSharedPtr<FSetRecoverValueByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSetRecoverValueByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetRecoverValue() const;
        FString GetRecoverValueString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetRecoverValueByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRecoverValueByUserIdRequest, ESPMode::ThreadSafe> FSetRecoverValueByUserIdRequestPtr;
}
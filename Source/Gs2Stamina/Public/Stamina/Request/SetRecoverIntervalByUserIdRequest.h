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
    class FSetRecoverIntervalByUserIdRequest;

    class GS2STAMINA_API FSetRecoverIntervalByUserIdRequest final : public TSharedFromThis<FSetRecoverIntervalByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> StaminaNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> RecoverIntervalMinutesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetRecoverIntervalByUserIdRequest();
        FSetRecoverIntervalByUserIdRequest(
            const FSetRecoverIntervalByUserIdRequest& From
        );
        ~FSetRecoverIntervalByUserIdRequest() = default;

        TSharedPtr<FSetRecoverIntervalByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetRecoverIntervalByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetRecoverIntervalByUserIdRequest> WithStaminaName(const TOptional<FString> StaminaName);
        TSharedPtr<FSetRecoverIntervalByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetRecoverIntervalByUserIdRequest> WithRecoverIntervalMinutes(const TOptional<int32> RecoverIntervalMinutes);
        TSharedPtr<FSetRecoverIntervalByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetStaminaName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetRecoverIntervalMinutes() const;
        FString GetRecoverIntervalMinutesString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetRecoverIntervalByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRecoverIntervalByUserIdRequest, ESPMode::ThreadSafe> FSetRecoverIntervalByUserIdRequestPtr;
}
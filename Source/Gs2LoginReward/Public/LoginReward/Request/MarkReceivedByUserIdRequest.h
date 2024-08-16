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

namespace Gs2::LoginReward::Request
{
    class FMarkReceivedByUserIdRequest;

    class GS2LOGINREWARD_API FMarkReceivedByUserIdRequest final : public TSharedFromThis<FMarkReceivedByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> StepNumberValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FMarkReceivedByUserIdRequest();
        FMarkReceivedByUserIdRequest(
            const FMarkReceivedByUserIdRequest& From
        );
        ~FMarkReceivedByUserIdRequest() = default;

        TSharedPtr<FMarkReceivedByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FMarkReceivedByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FMarkReceivedByUserIdRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FMarkReceivedByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMarkReceivedByUserIdRequest> WithStepNumber(const TOptional<int32> StepNumber);
        TSharedPtr<FMarkReceivedByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FMarkReceivedByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetStepNumber() const;
        FString GetStepNumberString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FMarkReceivedByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequestPtr;
}
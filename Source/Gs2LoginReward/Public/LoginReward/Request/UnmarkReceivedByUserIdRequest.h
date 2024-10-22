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
    class FUnmarkReceivedByUserIdRequest;

    class GS2LOGINREWARD_API FUnmarkReceivedByUserIdRequest final : public TSharedFromThis<FUnmarkReceivedByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> StepNumberValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnmarkReceivedByUserIdRequest();
        FUnmarkReceivedByUserIdRequest(
            const FUnmarkReceivedByUserIdRequest& From
        );
        ~FUnmarkReceivedByUserIdRequest() = default;

        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithStepNumber(const TOptional<int32> StepNumber);
        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUnmarkReceivedByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetStepNumber() const;
        FString GetStepNumberString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnmarkReceivedByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnmarkReceivedByUserIdRequest> FUnmarkReceivedByUserIdRequestPtr;
}
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

namespace Gs2::Mission::Request
{
    class FVerifyCompleteByUserIdRequest;

    class GS2MISSION_API FVerifyCompleteByUserIdRequest final : public TSharedFromThis<FVerifyCompleteByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> MissionTaskNameValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCompleteByUserIdRequest();
        FVerifyCompleteByUserIdRequest(
            const FVerifyCompleteByUserIdRequest& From
        );
        ~FVerifyCompleteByUserIdRequest() = default;

        TSharedPtr<FVerifyCompleteByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithMissionTaskName(const TOptional<FString> MissionTaskName);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyCompleteByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetMissionTaskName() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCompleteByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCompleteByUserIdRequest> FVerifyCompleteByUserIdRequestPtr;
}
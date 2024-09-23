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

namespace Gs2::Mission::Request
{
    class FVerifyCompleteRequest;

    class GS2MISSION_API FVerifyCompleteRequest final : public TSharedFromThis<FVerifyCompleteRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> MissionTaskNameValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCompleteRequest();
        FVerifyCompleteRequest(
            const FVerifyCompleteRequest& From
        );
        ~FVerifyCompleteRequest() = default;

        TSharedPtr<FVerifyCompleteRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCompleteRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCompleteRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FVerifyCompleteRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyCompleteRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCompleteRequest> WithMissionTaskName(const TOptional<FString> MissionTaskName);
        TSharedPtr<FVerifyCompleteRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyCompleteRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetMissionTaskName() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCompleteRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCompleteRequest, ESPMode::ThreadSafe> FVerifyCompleteRequestPtr;
}
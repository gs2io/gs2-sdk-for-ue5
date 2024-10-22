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
    class FRevertReceiveByUserIdRequest;

    class GS2MISSION_API FRevertReceiveByUserIdRequest final : public TSharedFromThis<FRevertReceiveByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> MissionTaskNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRevertReceiveByUserIdRequest();
        FRevertReceiveByUserIdRequest(
            const FRevertReceiveByUserIdRequest& From
        );
        ~FRevertReceiveByUserIdRequest() = default;

        TSharedPtr<FRevertReceiveByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRevertReceiveByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRevertReceiveByUserIdRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FRevertReceiveByUserIdRequest> WithMissionTaskName(const TOptional<FString> MissionTaskName);
        TSharedPtr<FRevertReceiveByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRevertReceiveByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRevertReceiveByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetMissionTaskName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRevertReceiveByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRevertReceiveByUserIdRequest> FRevertReceiveByUserIdRequestPtr;
}
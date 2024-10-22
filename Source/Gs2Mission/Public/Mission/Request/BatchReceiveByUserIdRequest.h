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
    class FBatchReceiveByUserIdRequest;

    class GS2MISSION_API FBatchReceiveByUserIdRequest final : public TSharedFromThis<FBatchReceiveByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> MissionTaskNamesValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBatchReceiveByUserIdRequest();
        FBatchReceiveByUserIdRequest(
            const FBatchReceiveByUserIdRequest& From
        );
        ~FBatchReceiveByUserIdRequest() = default;

        TSharedPtr<FBatchReceiveByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchReceiveByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBatchReceiveByUserIdRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FBatchReceiveByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBatchReceiveByUserIdRequest> WithMissionTaskNames(
            const TSharedPtr<TArray<FString>> MissionTaskNames);
        TSharedPtr<FBatchReceiveByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FBatchReceiveByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetMissionTaskNames() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBatchReceiveByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchReceiveByUserIdRequest> FBatchReceiveByUserIdRequestPtr;
}
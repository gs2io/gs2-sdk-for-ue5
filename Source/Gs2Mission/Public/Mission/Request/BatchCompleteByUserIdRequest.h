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
#include "../Model/Config.h"

namespace Gs2::Mission::Request
{
    class FBatchCompleteByUserIdRequest;

    class GS2MISSION_API FBatchCompleteByUserIdRequest final : public TSharedFromThis<FBatchCompleteByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> MissionTaskNamesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBatchCompleteByUserIdRequest();
        FBatchCompleteByUserIdRequest(
            const FBatchCompleteByUserIdRequest& From
        );
        ~FBatchCompleteByUserIdRequest() = default;

        TSharedPtr<FBatchCompleteByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithMissionTaskNames(
            const TSharedPtr<TArray<FString>> MissionTaskNames);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FBatchCompleteByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetMissionTaskNames() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBatchCompleteByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchCompleteByUserIdRequest, ESPMode::ThreadSafe> FBatchCompleteByUserIdRequestPtr;
}
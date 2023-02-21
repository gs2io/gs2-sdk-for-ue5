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
    class FCompleteByUserIdRequest;

    class GS2MISSION_API FCompleteByUserIdRequest final : public TSharedFromThis<FCompleteByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> MissionTaskNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCompleteByUserIdRequest();
        FCompleteByUserIdRequest(
            const FCompleteByUserIdRequest& From
        );
        ~FCompleteByUserIdRequest() = default;

        TSharedPtr<FCompleteByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCompleteByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCompleteByUserIdRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FCompleteByUserIdRequest> WithMissionTaskName(const TOptional<FString> MissionTaskName);
        TSharedPtr<FCompleteByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCompleteByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FCompleteByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetMissionTaskName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCompleteByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCompleteByUserIdRequest, ESPMode::ThreadSafe> FCompleteByUserIdRequestPtr;
}
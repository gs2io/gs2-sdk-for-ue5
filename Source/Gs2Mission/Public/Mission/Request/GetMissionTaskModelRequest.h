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
    class FGetMissionTaskModelRequest;

    class GS2MISSION_API FGetMissionTaskModelRequest final : public TSharedFromThis<FGetMissionTaskModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> MissionTaskNameValue;
        
    public:
        
        FGetMissionTaskModelRequest();
        FGetMissionTaskModelRequest(
            const FGetMissionTaskModelRequest& From
        );
        ~FGetMissionTaskModelRequest() = default;

        TSharedPtr<FGetMissionTaskModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMissionTaskModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMissionTaskModelRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FGetMissionTaskModelRequest> WithMissionTaskName(const TOptional<FString> MissionTaskName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetMissionTaskName() const;

        static TSharedPtr<FGetMissionTaskModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMissionTaskModelRequest, ESPMode::ThreadSafe> FGetMissionTaskModelRequestPtr;
}
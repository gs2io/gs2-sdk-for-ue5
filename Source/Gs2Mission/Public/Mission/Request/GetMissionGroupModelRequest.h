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
    class FGetMissionGroupModelRequest;

    class GS2MISSION_API FGetMissionGroupModelRequest final : public TSharedFromThis<FGetMissionGroupModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        
    public:
        
        FGetMissionGroupModelRequest();
        FGetMissionGroupModelRequest(
            const FGetMissionGroupModelRequest& From
        );
        ~FGetMissionGroupModelRequest() = default;

        TSharedPtr<FGetMissionGroupModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetMissionGroupModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetMissionGroupModelRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;

        static TSharedPtr<FGetMissionGroupModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMissionGroupModelRequest> FGetMissionGroupModelRequestPtr;
}
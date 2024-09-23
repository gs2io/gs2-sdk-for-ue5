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
    class FBatchCompleteRequest;

    class GS2MISSION_API FBatchCompleteRequest final : public TSharedFromThis<FBatchCompleteRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<FString>> MissionTaskNamesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FBatchCompleteRequest();
        FBatchCompleteRequest(
            const FBatchCompleteRequest& From
        );
        ~FBatchCompleteRequest() = default;

        TSharedPtr<FBatchCompleteRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FBatchCompleteRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FBatchCompleteRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FBatchCompleteRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FBatchCompleteRequest> WithMissionTaskNames(
            const TSharedPtr<TArray<FString>> MissionTaskNames);
        TSharedPtr<FBatchCompleteRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FBatchCompleteRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetAccessToken() const;
        TSharedPtr<TArray<FString>> GetMissionTaskNames() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FBatchCompleteRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchCompleteRequest, ESPMode::ThreadSafe> FBatchCompleteRequestPtr;
}
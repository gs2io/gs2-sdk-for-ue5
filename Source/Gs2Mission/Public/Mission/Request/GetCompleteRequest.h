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
    class FGetCompleteRequest;

    class GS2MISSION_API FGetCompleteRequest final : public TSharedFromThis<FGetCompleteRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetCompleteRequest();
        FGetCompleteRequest(
            const FGetCompleteRequest& From
        );
        ~FGetCompleteRequest() = default;

        TSharedPtr<FGetCompleteRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCompleteRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetCompleteRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FGetCompleteRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetCompleteRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCompleteRequest, ESPMode::ThreadSafe> FGetCompleteRequestPtr;
}
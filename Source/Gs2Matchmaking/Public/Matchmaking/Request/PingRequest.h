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

namespace Gs2::Matchmaking::Request
{
    class FPingRequest;

    class GS2MATCHMAKING_API FPingRequest final : public TSharedFromThis<FPingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPingRequest();
        FPingRequest(
            const FPingRequest& From
        );
        ~FPingRequest() = default;

        TSharedPtr<FPingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPingRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FPingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPingRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPingRequest, ESPMode::ThreadSafe> FPingRequestPtr;
}
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
    class FEarlyCompleteRequest;

    class GS2MATCHMAKING_API FEarlyCompleteRequest final : public TSharedFromThis<FEarlyCompleteRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FEarlyCompleteRequest();
        FEarlyCompleteRequest(
            const FEarlyCompleteRequest& From
        );
        ~FEarlyCompleteRequest() = default;

        TSharedPtr<FEarlyCompleteRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FEarlyCompleteRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FEarlyCompleteRequest> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FEarlyCompleteRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FEarlyCompleteRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FEarlyCompleteRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEarlyCompleteRequest, ESPMode::ThreadSafe> FEarlyCompleteRequestPtr;
}
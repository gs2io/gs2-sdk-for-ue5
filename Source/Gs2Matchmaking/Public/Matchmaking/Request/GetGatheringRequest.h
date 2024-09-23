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
    class FGetGatheringRequest;

    class GS2MATCHMAKING_API FGetGatheringRequest final : public TSharedFromThis<FGetGatheringRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GatheringNameValue;
        
    public:
        
        FGetGatheringRequest();
        FGetGatheringRequest(
            const FGetGatheringRequest& From
        );
        ~FGetGatheringRequest() = default;

        TSharedPtr<FGetGatheringRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetGatheringRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetGatheringRequest> WithGatheringName(const TOptional<FString> GatheringName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGatheringName() const;

        static TSharedPtr<FGetGatheringRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGatheringRequest, ESPMode::ThreadSafe> FGetGatheringRequestPtr;
}
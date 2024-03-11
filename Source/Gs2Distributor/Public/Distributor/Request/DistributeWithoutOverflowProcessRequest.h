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
#include "../Model/DistributeResource.h"

namespace Gs2::Distributor::Request
{
    class FDistributeWithoutOverflowProcessRequest;

    class GS2DISTRIBUTOR_API FDistributeWithoutOverflowProcessRequest final : public TSharedFromThis<FDistributeWithoutOverflowProcessRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FDistributeResource> DistributeResourceValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDistributeWithoutOverflowProcessRequest();
        FDistributeWithoutOverflowProcessRequest(
            const FDistributeWithoutOverflowProcessRequest& From
        );
        ~FDistributeWithoutOverflowProcessRequest() = default;

        TSharedPtr<FDistributeWithoutOverflowProcessRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDistributeWithoutOverflowProcessRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDistributeWithoutOverflowProcessRequest> WithDistributeResource(const TSharedPtr<Model::FDistributeResource> DistributeResource);
        TSharedPtr<FDistributeWithoutOverflowProcessRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FDistributeResource> GetDistributeResource() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDistributeWithoutOverflowProcessRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDistributeWithoutOverflowProcessRequest, ESPMode::ThreadSafe> FDistributeWithoutOverflowProcessRequestPtr;
}
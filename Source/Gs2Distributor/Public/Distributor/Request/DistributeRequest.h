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
#include "../Model/DistributeResource.h"

namespace Gs2::Distributor::Request
{
    class FDistributeRequest;

    class GS2DISTRIBUTOR_API FDistributeRequest final : public TSharedFromThis<FDistributeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DistributorNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Model::FDistributeResource> DistributeResourceValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDistributeRequest();
        FDistributeRequest(
            const FDistributeRequest& From
        );
        ~FDistributeRequest() = default;

        TSharedPtr<FDistributeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDistributeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDistributeRequest> WithDistributorName(const TOptional<FString> DistributorName);
        TSharedPtr<FDistributeRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDistributeRequest> WithDistributeResource(const TSharedPtr<Model::FDistributeResource> DistributeResource);
        TSharedPtr<FDistributeRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDistributeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDistributorName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<Model::FDistributeResource> GetDistributeResource() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDistributeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDistributeRequest> FDistributeRequestPtr;
}
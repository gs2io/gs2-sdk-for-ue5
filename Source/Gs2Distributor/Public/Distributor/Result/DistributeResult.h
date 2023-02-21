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

namespace Gs2::Distributor::Result
{
    class GS2DISTRIBUTOR_API FDistributeResult final : public TSharedFromThis<FDistributeResult>
    {
        TSharedPtr<Model::FDistributeResource> DistributeResourceValue;
        TOptional<FString> InboxNamespaceIdValue;
        TOptional<FString> ResultValue;
        
    public:
        
        FDistributeResult();
        FDistributeResult(
            const FDistributeResult& From
        );
        ~FDistributeResult() = default;

        TSharedPtr<FDistributeResult> WithDistributeResource(const TSharedPtr<Model::FDistributeResource> DistributeResource);
        TSharedPtr<FDistributeResult> WithInboxNamespaceId(const TOptional<FString> InboxNamespaceId);
        TSharedPtr<FDistributeResult> WithResult(const TOptional<FString> Result);

        TSharedPtr<Model::FDistributeResource> GetDistributeResource() const;
        TOptional<FString> GetInboxNamespaceId() const;
        TOptional<FString> GetResult() const;

        static TSharedPtr<FDistributeResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDistributeResult, ESPMode::ThreadSafe> FDistributeResultPtr;
}
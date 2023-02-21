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
    class GS2DISTRIBUTOR_API FDistributeWithoutOverflowProcessResult final : public TSharedFromThis<FDistributeWithoutOverflowProcessResult>
    {
        TSharedPtr<Model::FDistributeResource> DistributeResourceValue;
        TOptional<FString> ResultValue;
        
    public:
        
        FDistributeWithoutOverflowProcessResult();
        FDistributeWithoutOverflowProcessResult(
            const FDistributeWithoutOverflowProcessResult& From
        );
        ~FDistributeWithoutOverflowProcessResult() = default;

        TSharedPtr<FDistributeWithoutOverflowProcessResult> WithDistributeResource(const TSharedPtr<Model::FDistributeResource> DistributeResource);
        TSharedPtr<FDistributeWithoutOverflowProcessResult> WithResult(const TOptional<FString> Result);

        TSharedPtr<Model::FDistributeResource> GetDistributeResource() const;
        TOptional<FString> GetResult() const;

        static TSharedPtr<FDistributeWithoutOverflowProcessResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDistributeWithoutOverflowProcessResult, ESPMode::ThreadSafe> FDistributeWithoutOverflowProcessResultPtr;
}
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
#include "../Model/DistributorModel.h"

namespace Gs2::Distributor::Result
{
    class GS2DISTRIBUTOR_API FGetDistributorModelResult final : public TSharedFromThis<FGetDistributorModelResult>
    {
        TSharedPtr<Model::FDistributorModel> ItemValue;
        
    public:
        
        FGetDistributorModelResult();
        FGetDistributorModelResult(
            const FGetDistributorModelResult& From
        );
        ~FGetDistributorModelResult() = default;

        TSharedPtr<FGetDistributorModelResult> WithItem(const TSharedPtr<Model::FDistributorModel> Item);

        TSharedPtr<Model::FDistributorModel> GetItem() const;

        static TSharedPtr<FGetDistributorModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetDistributorModelResult, ESPMode::ThreadSafe> FGetDistributorModelResultPtr;
}
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
#include "../Model/SalesItemMaster.h"

namespace Gs2::Showcase::Result
{
    class GS2SHOWCASE_API FCreateSalesItemMasterResult final : public TSharedFromThis<FCreateSalesItemMasterResult>
    {
        TSharedPtr<Model::FSalesItemMaster> ItemValue;
        
    public:
        
        FCreateSalesItemMasterResult();
        FCreateSalesItemMasterResult(
            const FCreateSalesItemMasterResult& From
        );
        ~FCreateSalesItemMasterResult() = default;

        TSharedPtr<FCreateSalesItemMasterResult> WithItem(const TSharedPtr<Model::FSalesItemMaster> Item);

        TSharedPtr<Model::FSalesItemMaster> GetItem() const;

        static TSharedPtr<FCreateSalesItemMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSalesItemMasterResult, ESPMode::ThreadSafe> FCreateSalesItemMasterResultPtr;
}
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
#include "../Model/CurrentCampaignMaster.h"

namespace Gs2::SerialKey::Result
{
    class GS2SERIALKEY_API FUpdateCurrentCampaignMasterResult final : public TSharedFromThis<FUpdateCurrentCampaignMasterResult>
    {
        TSharedPtr<Model::FCurrentCampaignMaster> ItemValue;
        
    public:
        
        FUpdateCurrentCampaignMasterResult();
        FUpdateCurrentCampaignMasterResult(
            const FUpdateCurrentCampaignMasterResult& From
        );
        ~FUpdateCurrentCampaignMasterResult() = default;

        TSharedPtr<FUpdateCurrentCampaignMasterResult> WithItem(const TSharedPtr<Model::FCurrentCampaignMaster> Item);

        TSharedPtr<Model::FCurrentCampaignMaster> GetItem() const;

        static TSharedPtr<FUpdateCurrentCampaignMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentCampaignMasterResult, ESPMode::ThreadSafe> FUpdateCurrentCampaignMasterResultPtr;
}
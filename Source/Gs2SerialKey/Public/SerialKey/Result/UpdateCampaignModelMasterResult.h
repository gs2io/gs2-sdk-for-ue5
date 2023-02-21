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
#include "../Model/CampaignModelMaster.h"

namespace Gs2::SerialKey::Result
{
    class GS2SERIALKEY_API FUpdateCampaignModelMasterResult final : public TSharedFromThis<FUpdateCampaignModelMasterResult>
    {
        TSharedPtr<Model::FCampaignModelMaster> ItemValue;
        
    public:
        
        FUpdateCampaignModelMasterResult();
        FUpdateCampaignModelMasterResult(
            const FUpdateCampaignModelMasterResult& From
        );
        ~FUpdateCampaignModelMasterResult() = default;

        TSharedPtr<FUpdateCampaignModelMasterResult> WithItem(const TSharedPtr<Model::FCampaignModelMaster> Item);

        TSharedPtr<Model::FCampaignModelMaster> GetItem() const;

        static TSharedPtr<FUpdateCampaignModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCampaignModelMasterResult, ESPMode::ThreadSafe> FUpdateCampaignModelMasterResultPtr;
}
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
#include "../Model/CampaignModel.h"

namespace Gs2::SerialKey::Result
{
    class GS2SERIALKEY_API FGetCampaignModelResult final : public TSharedFromThis<FGetCampaignModelResult>
    {
        TSharedPtr<Model::FCampaignModel> ItemValue;
        
    public:
        
        FGetCampaignModelResult();
        FGetCampaignModelResult(
            const FGetCampaignModelResult& From
        );
        ~FGetCampaignModelResult() = default;

        TSharedPtr<FGetCampaignModelResult> WithItem(const TSharedPtr<Model::FCampaignModel> Item);

        TSharedPtr<Model::FCampaignModel> GetItem() const;

        static TSharedPtr<FGetCampaignModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCampaignModelResult, ESPMode::ThreadSafe> FGetCampaignModelResultPtr;
}
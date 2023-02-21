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
#include "../Model/SerialKey.h"
#include "../Model/CampaignModel.h"

namespace Gs2::SerialKey::Result
{
    class GS2SERIALKEY_API FUseByUserIdResult final : public TSharedFromThis<FUseByUserIdResult>
    {
        TSharedPtr<Model::FSerialKey> ItemValue;
        TSharedPtr<Model::FCampaignModel> CampaignModelValue;
        
    public:
        
        FUseByUserIdResult();
        FUseByUserIdResult(
            const FUseByUserIdResult& From
        );
        ~FUseByUserIdResult() = default;

        TSharedPtr<FUseByUserIdResult> WithItem(const TSharedPtr<Model::FSerialKey> Item);
        TSharedPtr<FUseByUserIdResult> WithCampaignModel(const TSharedPtr<Model::FCampaignModel> CampaignModel);

        TSharedPtr<Model::FSerialKey> GetItem() const;
        TSharedPtr<Model::FCampaignModel> GetCampaignModel() const;

        static TSharedPtr<FUseByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUseByUserIdResult, ESPMode::ThreadSafe> FUseByUserIdResultPtr;
}
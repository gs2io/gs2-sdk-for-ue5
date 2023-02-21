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
    class GS2SERIALKEY_API FUseByStampTaskResult final : public TSharedFromThis<FUseByStampTaskResult>
    {
        TSharedPtr<Model::FSerialKey> ItemValue;
        TSharedPtr<Model::FCampaignModel> CampaignModelValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FUseByStampTaskResult();
        FUseByStampTaskResult(
            const FUseByStampTaskResult& From
        );
        ~FUseByStampTaskResult() = default;

        TSharedPtr<FUseByStampTaskResult> WithItem(const TSharedPtr<Model::FSerialKey> Item);
        TSharedPtr<FUseByStampTaskResult> WithCampaignModel(const TSharedPtr<Model::FCampaignModel> CampaignModel);
        TSharedPtr<FUseByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FSerialKey> GetItem() const;
        TSharedPtr<Model::FCampaignModel> GetCampaignModel() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FUseByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUseByStampTaskResult, ESPMode::ThreadSafe> FUseByStampTaskResultPtr;
}
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
    class GS2SERIALKEY_API FDescribeCampaignModelMastersResult final : public TSharedFromThis<FDescribeCampaignModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FCampaignModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeCampaignModelMastersResult();
        FDescribeCampaignModelMastersResult(
            const FDescribeCampaignModelMastersResult& From
        );
        ~FDescribeCampaignModelMastersResult() = default;

        TSharedPtr<FDescribeCampaignModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FCampaignModelMaster>>> Items);
        TSharedPtr<FDescribeCampaignModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FCampaignModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeCampaignModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeCampaignModelMastersResult, ESPMode::ThreadSafe> FDescribeCampaignModelMastersResultPtr;
}
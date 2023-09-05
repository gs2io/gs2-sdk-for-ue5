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
#include "../Model/RarityParameterStatus.h"

namespace Gs2::Enchant::Result
{
    class GS2ENCHANT_API FSetRarityParameterStatusByStampSheetResult final : public TSharedFromThis<FSetRarityParameterStatusByStampSheetResult>
    {
        TSharedPtr<Model::FRarityParameterStatus> ItemValue;
        TSharedPtr<Model::FRarityParameterStatus> OldValue;
        
    public:
        
        FSetRarityParameterStatusByStampSheetResult();
        FSetRarityParameterStatusByStampSheetResult(
            const FSetRarityParameterStatusByStampSheetResult& From
        );
        ~FSetRarityParameterStatusByStampSheetResult() = default;

        TSharedPtr<FSetRarityParameterStatusByStampSheetResult> WithItem(const TSharedPtr<Model::FRarityParameterStatus> Item);
        TSharedPtr<FSetRarityParameterStatusByStampSheetResult> WithOld(const TSharedPtr<Model::FRarityParameterStatus> Old);

        TSharedPtr<Model::FRarityParameterStatus> GetItem() const;
        TSharedPtr<Model::FRarityParameterStatus> GetOld() const;

        static TSharedPtr<FSetRarityParameterStatusByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRarityParameterStatusByStampSheetResult, ESPMode::ThreadSafe> FSetRarityParameterStatusByStampSheetResultPtr;
}
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
    class GS2ENCHANT_API FReDrawRarityParameterStatusByStampSheetResult final : public TSharedFromThis<FReDrawRarityParameterStatusByStampSheetResult>
    {
        TSharedPtr<Model::FRarityParameterStatus> ItemValue;
        
    public:
        
        FReDrawRarityParameterStatusByStampSheetResult();
        FReDrawRarityParameterStatusByStampSheetResult(
            const FReDrawRarityParameterStatusByStampSheetResult& From
        );
        ~FReDrawRarityParameterStatusByStampSheetResult() = default;

        TSharedPtr<FReDrawRarityParameterStatusByStampSheetResult> WithItem(const TSharedPtr<Model::FRarityParameterStatus> Item);

        TSharedPtr<Model::FRarityParameterStatus> GetItem() const;

        static TSharedPtr<FReDrawRarityParameterStatusByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReDrawRarityParameterStatusByStampSheetResult, ESPMode::ThreadSafe> FReDrawRarityParameterStatusByStampSheetResultPtr;
}
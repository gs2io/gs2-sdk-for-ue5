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
#include "../Model/Counter.h"
#include "../Model/Complete.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FSetByStampSheetResult final : public TSharedFromThis<FSetByStampSheetResult>
    {
        TSharedPtr<Model::FCounter> ItemValue;
        TSharedPtr<Model::FCounter> OldValue;
        TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> ChangedCompletesValue;
        
    public:
        
        FSetByStampSheetResult();
        FSetByStampSheetResult(
            const FSetByStampSheetResult& From
        );
        ~FSetByStampSheetResult() = default;

        TSharedPtr<FSetByStampSheetResult> WithItem(const TSharedPtr<Model::FCounter> Item);
        TSharedPtr<FSetByStampSheetResult> WithOld(const TSharedPtr<Model::FCounter> Old);
        TSharedPtr<FSetByStampSheetResult> WithChangedCompletes(const TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> ChangedCompletes);

        TSharedPtr<Model::FCounter> GetItem() const;
        TSharedPtr<Model::FCounter> GetOld() const;
        TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> GetChangedCompletes() const;

        static TSharedPtr<FSetByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetByStampSheetResult, ESPMode::ThreadSafe> FSetByStampSheetResultPtr;
}
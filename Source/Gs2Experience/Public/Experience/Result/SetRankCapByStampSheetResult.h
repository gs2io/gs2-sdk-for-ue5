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
#include "../Model/Status.h"

namespace Gs2::Experience::Result
{
    class GS2EXPERIENCE_API FSetRankCapByStampSheetResult final : public TSharedFromThis<FSetRankCapByStampSheetResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        TSharedPtr<Model::FStatus> OldValue;
        
    public:
        
        FSetRankCapByStampSheetResult();
        FSetRankCapByStampSheetResult(
            const FSetRankCapByStampSheetResult& From
        );
        ~FSetRankCapByStampSheetResult() = default;

        TSharedPtr<FSetRankCapByStampSheetResult> WithItem(const TSharedPtr<Model::FStatus> Item);
        TSharedPtr<FSetRankCapByStampSheetResult> WithOld(const TSharedPtr<Model::FStatus> Old);

        TSharedPtr<Model::FStatus> GetItem() const;
        TSharedPtr<Model::FStatus> GetOld() const;

        static TSharedPtr<FSetRankCapByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetRankCapByStampSheetResult, ESPMode::ThreadSafe> FSetRankCapByStampSheetResultPtr;
}
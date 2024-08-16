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
#include "../Model/Profile.h"

namespace Gs2::Friend::Result
{
    class GS2FRIEND_API FUpdateProfileByStampSheetResult final : public TSharedFromThis<FUpdateProfileByStampSheetResult>
    {
        TSharedPtr<Model::FProfile> ItemValue;
        
    public:
        
        FUpdateProfileByStampSheetResult();
        FUpdateProfileByStampSheetResult(
            const FUpdateProfileByStampSheetResult& From
        );
        ~FUpdateProfileByStampSheetResult() = default;

        TSharedPtr<FUpdateProfileByStampSheetResult> WithItem(const TSharedPtr<Model::FProfile> Item);

        TSharedPtr<Model::FProfile> GetItem() const;

        static TSharedPtr<FUpdateProfileByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateProfileByStampSheetResult, ESPMode::ThreadSafe> FUpdateProfileByStampSheetResultPtr;
}
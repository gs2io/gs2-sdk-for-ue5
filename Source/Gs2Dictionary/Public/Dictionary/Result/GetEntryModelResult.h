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
#include "../Model/EntryModel.h"

namespace Gs2::Dictionary::Result
{
    class GS2DICTIONARY_API FGetEntryModelResult final : public TSharedFromThis<FGetEntryModelResult>
    {
        TSharedPtr<Model::FEntryModel> ItemValue;
        
    public:
        
        FGetEntryModelResult();
        FGetEntryModelResult(
            const FGetEntryModelResult& From
        );
        ~FGetEntryModelResult() = default;

        TSharedPtr<FGetEntryModelResult> WithItem(const TSharedPtr<Model::FEntryModel> Item);

        TSharedPtr<Model::FEntryModel> GetItem() const;

        static TSharedPtr<FGetEntryModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEntryModelResult, ESPMode::ThreadSafe> FGetEntryModelResultPtr;
}
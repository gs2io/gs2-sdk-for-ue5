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
#include "../Model/StoreContentModel.h"

namespace Gs2::Money2::Result
{
    class GS2MONEY2_API FGetStoreContentModelResult final : public TSharedFromThis<FGetStoreContentModelResult>
    {
        TSharedPtr<Model::FStoreContentModel> ItemValue;
        
    public:
        
        FGetStoreContentModelResult();
        FGetStoreContentModelResult(
            const FGetStoreContentModelResult& From
        );
        ~FGetStoreContentModelResult() = default;

        TSharedPtr<FGetStoreContentModelResult> WithItem(const TSharedPtr<Model::FStoreContentModel> Item);

        TSharedPtr<Model::FStoreContentModel> GetItem() const;

        static TSharedPtr<FGetStoreContentModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStoreContentModelResult, ESPMode::ThreadSafe> FGetStoreContentModelResultPtr;
}
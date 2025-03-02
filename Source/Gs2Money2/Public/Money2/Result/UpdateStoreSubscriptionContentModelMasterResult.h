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
#include "../Model/StoreSubscriptionContentModelMaster.h"

namespace Gs2::Money2::Result
{
    class GS2MONEY2_API FUpdateStoreSubscriptionContentModelMasterResult final : public TSharedFromThis<FUpdateStoreSubscriptionContentModelMasterResult>
    {
        TSharedPtr<Model::FStoreSubscriptionContentModelMaster> ItemValue;
        
    public:
        
        FUpdateStoreSubscriptionContentModelMasterResult();
        FUpdateStoreSubscriptionContentModelMasterResult(
            const FUpdateStoreSubscriptionContentModelMasterResult& From
        );
        ~FUpdateStoreSubscriptionContentModelMasterResult() = default;

        TSharedPtr<FUpdateStoreSubscriptionContentModelMasterResult> WithItem(const TSharedPtr<Model::FStoreSubscriptionContentModelMaster> Item);

        TSharedPtr<Model::FStoreSubscriptionContentModelMaster> GetItem() const;

        static TSharedPtr<FUpdateStoreSubscriptionContentModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStoreSubscriptionContentModelMasterResult, ESPMode::ThreadSafe> FUpdateStoreSubscriptionContentModelMasterResultPtr;
}
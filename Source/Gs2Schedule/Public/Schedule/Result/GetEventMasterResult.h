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
#include "../Model/EventMaster.h"

namespace Gs2::Schedule::Result
{
    class GS2SCHEDULE_API FGetEventMasterResult final : public TSharedFromThis<FGetEventMasterResult>
    {
        TSharedPtr<Model::FEventMaster> ItemValue;
        
    public:
        
        FGetEventMasterResult();
        FGetEventMasterResult(
            const FGetEventMasterResult& From
        );
        ~FGetEventMasterResult() = default;

        TSharedPtr<FGetEventMasterResult> WithItem(const TSharedPtr<Model::FEventMaster> Item);

        TSharedPtr<Model::FEventMaster> GetItem() const;

        static TSharedPtr<FGetEventMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEventMasterResult, ESPMode::ThreadSafe> FGetEventMasterResultPtr;
}
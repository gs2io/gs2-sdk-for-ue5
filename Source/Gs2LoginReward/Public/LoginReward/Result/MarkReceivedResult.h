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
#include "../Model/ReceiveStatus.h"
#include "../Model/BonusModel.h"

namespace Gs2::LoginReward::Result
{
    class GS2LOGINREWARD_API FMarkReceivedResult final : public TSharedFromThis<FMarkReceivedResult>
    {
        TSharedPtr<Model::FReceiveStatus> ItemValue;
        TSharedPtr<Model::FBonusModel> BonusModelValue;
        
    public:
        
        FMarkReceivedResult();
        FMarkReceivedResult(
            const FMarkReceivedResult& From
        );
        ~FMarkReceivedResult() = default;

        TSharedPtr<FMarkReceivedResult> WithItem(const TSharedPtr<Model::FReceiveStatus> Item);
        TSharedPtr<FMarkReceivedResult> WithBonusModel(const TSharedPtr<Model::FBonusModel> BonusModel);

        TSharedPtr<Model::FReceiveStatus> GetItem() const;
        TSharedPtr<Model::FBonusModel> GetBonusModel() const;

        static TSharedPtr<FMarkReceivedResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMarkReceivedResult, ESPMode::ThreadSafe> FMarkReceivedResultPtr;
}
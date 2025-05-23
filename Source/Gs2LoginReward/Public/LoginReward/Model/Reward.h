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
#include "Core/Gs2Object.h"
#include "AcquireAction.h"

namespace Gs2::LoginReward::Model
{
    class GS2LOGINREWARD_API FReward final : public FGs2Object, public TSharedFromThis<FReward>
    {
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;

    public:
        FReward();
        FReward(
            const FReward& From
        );
        virtual ~FReward() override = default;

        TSharedPtr<FReward> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);

        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;


        static TSharedPtr<FReward> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FReward, ESPMode::ThreadSafe> FRewardPtr;
}
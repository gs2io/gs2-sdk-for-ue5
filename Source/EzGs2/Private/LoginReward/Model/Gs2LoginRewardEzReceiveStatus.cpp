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

#include "EzGs2/Public/LoginReward/Model/Gs2LoginRewardEzReceiveStatus.h"

namespace Gs2::UE5::LoginReward::Model
{

    TSharedPtr<FEzReceiveStatus> FEzReceiveStatus::WithBonusModelName(
        const TOptional<FString> BonusModelName
    )
    {
        this->BonusModelNameValue = BonusModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzReceiveStatus> FEzReceiveStatus::WithReceivedSteps(
        const TSharedPtr<TArray<bool>> ReceivedSteps
    )
    {
        this->ReceivedStepsValue = ReceivedSteps;
        return SharedThis(this);
    }

    TSharedPtr<FEzReceiveStatus> FEzReceiveStatus::WithLastReceivedAt(
        const TOptional<int64> LastReceivedAt
    )
    {
        this->LastReceivedAtValue = LastReceivedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzReceiveStatus::GetBonusModelName() const
    {
        return BonusModelNameValue;
    }
    TSharedPtr<TArray<bool>> FEzReceiveStatus::GetReceivedSteps() const
    {
        return ReceivedStepsValue;
    }
    TOptional<int64> FEzReceiveStatus::GetLastReceivedAt() const
    {
        return LastReceivedAtValue;
    }

    FString FEzReceiveStatus::GetLastReceivedAtString() const
    {
        if (!LastReceivedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastReceivedAtValue.GetValue());
    }

    Gs2::LoginReward::Model::FReceiveStatusPtr FEzReceiveStatus::ToModel() const
    {
        return MakeShared<Gs2::LoginReward::Model::FReceiveStatus>()
            ->WithBonusModelName(BonusModelNameValue)
            ->WithReceivedSteps(ReceivedStepsValue)
            ->WithLastReceivedAt(LastReceivedAtValue);
    }

    TSharedPtr<FEzReceiveStatus> FEzReceiveStatus::FromModel(const Gs2::LoginReward::Model::FReceiveStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzReceiveStatus>()
            ->WithBonusModelName(Model->GetBonusModelName())
            ->WithReceivedSteps(Model->GetReceivedSteps())
            ->WithLastReceivedAt(Model->GetLastReceivedAt());
    }
}
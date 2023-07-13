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
#include "LoginReward/Model/ReceiveStatus.h"

namespace Gs2::UE5::LoginReward::Model
{
	class EZGS2_API FEzReceiveStatus final : public TSharedFromThis<FEzReceiveStatus>
	{
        TOptional<FString> BonusModelNameValue;
        TSharedPtr<TArray<bool>> ReceivedStepsValue;
        TOptional<int64> LastReceivedAtValue;

	public:
        TSharedPtr<FEzReceiveStatus> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FEzReceiveStatus> WithReceivedSteps(const TSharedPtr<TArray<bool>> ReceivedSteps);
        TSharedPtr<FEzReceiveStatus> WithLastReceivedAt(const TOptional<int64> LastReceivedAt);

        TOptional<FString> GetBonusModelName() const;

        TSharedPtr<TArray<bool>> GetReceivedSteps() const;

        TOptional<int64> GetLastReceivedAt() const;
        FString GetLastReceivedAtString() const;

        Gs2::LoginReward::Model::FReceiveStatusPtr ToModel() const;
        static TSharedPtr<FEzReceiveStatus> FromModel(Gs2::LoginReward::Model::FReceiveStatusPtr Model);
    };
    typedef TSharedPtr<FEzReceiveStatus> FEzReceiveStatusPtr;
}
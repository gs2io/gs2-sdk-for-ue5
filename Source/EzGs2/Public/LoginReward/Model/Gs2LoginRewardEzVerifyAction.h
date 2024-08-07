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
#include "LoginReward/Model/VerifyAction.h"

namespace Gs2::UE5::LoginReward::Model
{
	class EZGS2_API FEzVerifyAction final : public TSharedFromThis<FEzVerifyAction>
	{
        TOptional<FString> ActionValue;
        TOptional<FString> RequestValue;

	public:
        TSharedPtr<FEzVerifyAction> WithAction(const TOptional<FString> Action);
        TSharedPtr<FEzVerifyAction> WithRequest(const TOptional<FString> Request);

        TOptional<FString> GetAction() const;

        TOptional<FString> GetRequest() const;

        Gs2::LoginReward::Model::FVerifyActionPtr ToModel() const;
        static TSharedPtr<FEzVerifyAction> FromModel(Gs2::LoginReward::Model::FVerifyActionPtr Model);
    };
    typedef TSharedPtr<FEzVerifyAction> FEzVerifyActionPtr;
}
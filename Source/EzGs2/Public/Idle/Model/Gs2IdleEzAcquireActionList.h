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
#include "Idle/Model/AcquireActionList.h"
#include "Gs2IdleEzAcquireAction.h"

namespace Gs2::UE5::Idle::Model
{
	class EZGS2_API FEzAcquireActionList final : public TSharedFromThis<FEzAcquireActionList>
	{
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>> AcquireActionsValue;

	public:
        TSharedPtr<FEzAcquireActionList> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>> AcquireActions);

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Idle::Model::FEzAcquireAction>>> GetAcquireActions() const;

        Gs2::Idle::Model::FAcquireActionListPtr ToModel() const;
        static TSharedPtr<FEzAcquireActionList> FromModel(Gs2::Idle::Model::FAcquireActionListPtr Model);
    };
    typedef TSharedPtr<FEzAcquireActionList> FEzAcquireActionListPtr;
}
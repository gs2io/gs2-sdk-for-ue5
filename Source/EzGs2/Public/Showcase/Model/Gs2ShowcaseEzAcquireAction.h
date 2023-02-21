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
#include "Showcase/Model/AcquireAction.h"

namespace Gs2::UE5::Showcase::Model
{
	class EZGS2_API FEzAcquireAction final : public TSharedFromThis<FEzAcquireAction>
	{
        TOptional<FString> ActionValue;
        TOptional<FString> RequestValue;

	public:
        TSharedPtr<FEzAcquireAction> WithAction(const TOptional<FString> Action);
        TSharedPtr<FEzAcquireAction> WithRequest(const TOptional<FString> Request);

        TOptional<FString> GetAction() const;

        TOptional<FString> GetRequest() const;

        Gs2::Showcase::Model::FAcquireActionPtr ToModel() const;
        static TSharedPtr<FEzAcquireAction> FromModel(Gs2::Showcase::Model::FAcquireActionPtr Model);
    };
    typedef TSharedPtr<FEzAcquireAction> FEzAcquireActionPtr;
}
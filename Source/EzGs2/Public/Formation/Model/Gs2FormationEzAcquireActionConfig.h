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
#include "Formation/Model/AcquireActionConfig.h"
#include "Gs2FormationEzConfig.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzAcquireActionConfig final : public TSharedFromThis<FEzAcquireActionConfig>
	{
        TOptional<FString> NameValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzConfig>>> ConfigValue;

	public:
        TSharedPtr<FEzAcquireActionConfig> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzAcquireActionConfig> WithConfig(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzConfig>>> Config);

        TOptional<FString> GetName() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzConfig>>> GetConfig() const;

        Gs2::Formation::Model::FAcquireActionConfigPtr ToModel() const;
        static TSharedPtr<FEzAcquireActionConfig> FromModel(Gs2::Formation::Model::FAcquireActionConfigPtr Model);
    };
    typedef TSharedPtr<FEzAcquireActionConfig> FEzAcquireActionConfigPtr;
}
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

namespace Gs2::AdReward::Model
{
    class GS2ADREWARD_API FAdMob final : public FGs2Object, public TSharedFromThis<FAdMob>
    {
        TSharedPtr<TArray<FString>> AllowAdUnitIdsValue;

    public:
        FAdMob();
        FAdMob(
            const FAdMob& From
        );
        virtual ~FAdMob() override = default;

        TSharedPtr<FAdMob> WithAllowAdUnitIds(const TSharedPtr<TArray<FString>> AllowAdUnitIds);

        TSharedPtr<TArray<FString>> GetAllowAdUnitIds() const;


        static TSharedPtr<FAdMob> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAdMob, ESPMode::ThreadSafe> FAdMobPtr;
}
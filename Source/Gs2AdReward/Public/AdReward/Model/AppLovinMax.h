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
    class GS2ADREWARD_API FAppLovinMax final : public Gs2Object, public TSharedFromThis<FAppLovinMax>
    {
        TOptional<FString> AllowAdUnitIdValue;
        TOptional<FString> EventKeyValue;

    public:
        FAppLovinMax();
        FAppLovinMax(
            const FAppLovinMax& From
        );
        virtual ~FAppLovinMax() override = default;

        TSharedPtr<FAppLovinMax> WithAllowAdUnitId(const TOptional<FString> AllowAdUnitId);
        TSharedPtr<FAppLovinMax> WithEventKey(const TOptional<FString> EventKey);

        TOptional<FString> GetAllowAdUnitId() const;
        TOptional<FString> GetEventKey() const;


        static TSharedPtr<FAppLovinMax> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAppLovinMax, ESPMode::ThreadSafe> FAppLovinMaxPtr;
}
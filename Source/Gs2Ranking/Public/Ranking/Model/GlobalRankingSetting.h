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
#include "FixedTiming.h"
#include "Scope.h"

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FGlobalRankingSetting final : public Gs2Object, public TSharedFromThis<FGlobalRankingSetting>
    {
        TOptional<bool> UniqueByUserIdValue;
        TOptional<int32> CalculateIntervalMinutesValue;
        TSharedPtr<FFixedTiming> CalculateFixedTimingValue;
        TSharedPtr<TArray<TSharedPtr<FScope>>> AdditionalScopesValue;
        TSharedPtr<TArray<FString>> IgnoreUserIdsValue;
        TOptional<FString> GenerationValue;

    public:
        FGlobalRankingSetting();
        FGlobalRankingSetting(
            const FGlobalRankingSetting& From
        );
        virtual ~FGlobalRankingSetting() override = default;

        TSharedPtr<FGlobalRankingSetting> WithUniqueByUserId(const TOptional<bool> UniqueByUserId);
        TSharedPtr<FGlobalRankingSetting> WithCalculateIntervalMinutes(const TOptional<int32> CalculateIntervalMinutes);
        TSharedPtr<FGlobalRankingSetting> WithCalculateFixedTiming(const TSharedPtr<FFixedTiming> CalculateFixedTiming);
        TSharedPtr<FGlobalRankingSetting> WithAdditionalScopes(const TSharedPtr<TArray<TSharedPtr<FScope>>> AdditionalScopes);
        TSharedPtr<FGlobalRankingSetting> WithIgnoreUserIds(const TSharedPtr<TArray<FString>> IgnoreUserIds);
        TSharedPtr<FGlobalRankingSetting> WithGeneration(const TOptional<FString> Generation);

        TOptional<bool> GetUniqueByUserId() const;
        FString GetUniqueByUserIdString() const;
        TOptional<int32> GetCalculateIntervalMinutes() const;
        FString GetCalculateIntervalMinutesString() const;
        TSharedPtr<FFixedTiming> GetCalculateFixedTiming() const;
        TSharedPtr<TArray<TSharedPtr<FScope>>> GetAdditionalScopes() const;
        TSharedPtr<TArray<FString>> GetIgnoreUserIds() const;
        TOptional<FString> GetGeneration() const;


        static TSharedPtr<FGlobalRankingSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGlobalRankingSetting, ESPMode::ThreadSafe> FGlobalRankingSettingPtr;
}
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

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FSubscribeUser final : public Gs2Object, public TSharedFromThis<FSubscribeUser>
    {
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;

    public:
        FSubscribeUser();
        FSubscribeUser(
            const FSubscribeUser& From
        );
        virtual ~FSubscribeUser() override = default;

        TSharedPtr<FSubscribeUser> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FSubscribeUser> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribeUser> WithTargetUserId(const TOptional<FString> TargetUserId);

        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetUserId() const;


        static TSharedPtr<FSubscribeUser> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribeUser, ESPMode::ThreadSafe> FSubscribeUserPtr;
}
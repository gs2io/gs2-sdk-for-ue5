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
#include "../Model/SeasonGathering.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FVerifyIncludeParticipantByStampTaskResult final : public TSharedFromThis<FVerifyIncludeParticipantByStampTaskResult>
    {
        TSharedPtr<Model::FSeasonGathering> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FVerifyIncludeParticipantByStampTaskResult();
        FVerifyIncludeParticipantByStampTaskResult(
            const FVerifyIncludeParticipantByStampTaskResult& From
        );
        ~FVerifyIncludeParticipantByStampTaskResult() = default;

        TSharedPtr<FVerifyIncludeParticipantByStampTaskResult> WithItem(const TSharedPtr<Model::FSeasonGathering> Item);
        TSharedPtr<FVerifyIncludeParticipantByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FSeasonGathering> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FVerifyIncludeParticipantByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyIncludeParticipantByStampTaskResult, ESPMode::ThreadSafe> FVerifyIncludeParticipantByStampTaskResultPtr;
}
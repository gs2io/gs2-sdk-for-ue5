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
#include "Dom/JsonObject.h"

namespace Gs2::Ranking2::Request
{
    class FVerifyGlobalRankingScoreByStampTaskRequest;

    class GS2RANKING2_API FVerifyGlobalRankingScoreByStampTaskRequest final : public TSharedFromThis<FVerifyGlobalRankingScoreByStampTaskRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StampTaskValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FVerifyGlobalRankingScoreByStampTaskRequest();
        FVerifyGlobalRankingScoreByStampTaskRequest(
            const FVerifyGlobalRankingScoreByStampTaskRequest& From
        );
        ~FVerifyGlobalRankingScoreByStampTaskRequest() = default;

        TSharedPtr<FVerifyGlobalRankingScoreByStampTaskRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyGlobalRankingScoreByStampTaskRequest> WithStampTask(const TOptional<FString> StampTask);
        TSharedPtr<FVerifyGlobalRankingScoreByStampTaskRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStampTask() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FVerifyGlobalRankingScoreByStampTaskRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyGlobalRankingScoreByStampTaskRequest> FVerifyGlobalRankingScoreByStampTaskRequestPtr;
}
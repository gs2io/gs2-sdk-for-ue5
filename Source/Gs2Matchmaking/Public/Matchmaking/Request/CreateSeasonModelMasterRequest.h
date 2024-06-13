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

namespace Gs2::Matchmaking::Request
{
    class FCreateSeasonModelMasterRequest;

    class GS2MATCHMAKING_API FCreateSeasonModelMasterRequest final : public TSharedFromThis<FCreateSeasonModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParticipantsValue;
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        
    public:
        
        FCreateSeasonModelMasterRequest();
        FCreateSeasonModelMasterRequest(
            const FCreateSeasonModelMasterRequest& From
        );
        ~FCreateSeasonModelMasterRequest() = default;

        TSharedPtr<FCreateSeasonModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithMaximumParticipants(const TOptional<int32> MaximumParticipants);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FCreateSeasonModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumParticipants() const;
        FString GetMaximumParticipantsString() const;
        TOptional<FString> GetExperienceModelId() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TSharedPtr<FCreateSeasonModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSeasonModelMasterRequest, ESPMode::ThreadSafe> FCreateSeasonModelMasterRequestPtr;
}
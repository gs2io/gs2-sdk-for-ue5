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
#include "../Model/Contents.h"
#include "../Model/AcquireAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::Quest::Request
{
    class FCreateQuestModelMasterRequest;

    class GS2QUEST_API FCreateQuestModelMasterRequest final : public TSharedFromThis<FCreateQuestModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FContents>>> ContentsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActionsValue;
        TSharedPtr<TArray<FString>> PremiseQuestNamesValue;
        
    public:
        
        FCreateQuestModelMasterRequest();
        FCreateQuestModelMasterRequest(
            const FCreateQuestModelMasterRequest& From
        );
        ~FCreateQuestModelMasterRequest() = default;

        TSharedPtr<FCreateQuestModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateQuestModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateQuestModelMasterRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FCreateQuestModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateQuestModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateQuestModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateQuestModelMasterRequest> WithContents(const TSharedPtr<TArray<TSharedPtr<Model::FContents>>> Contents);
        TSharedPtr<FCreateQuestModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FCreateQuestModelMasterRequest> WithFirstCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActions);
        TSharedPtr<FCreateQuestModelMasterRequest> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions);
        TSharedPtr<FCreateQuestModelMasterRequest> WithFailedAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActions);
        TSharedPtr<FCreateQuestModelMasterRequest> WithPremiseQuestNames(
            const TSharedPtr<TArray<FString>> PremiseQuestNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FContents>>> GetContents() const;
        TOptional<FString> GetChallengePeriodEventId() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetFirstCompleteAcquireActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetConsumeActions() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetFailedAcquireActions() const;
        TSharedPtr<TArray<FString>> GetPremiseQuestNames() const;

        static TSharedPtr<FCreateQuestModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateQuestModelMasterRequest, ESPMode::ThreadSafe> FCreateQuestModelMasterRequestPtr;
}
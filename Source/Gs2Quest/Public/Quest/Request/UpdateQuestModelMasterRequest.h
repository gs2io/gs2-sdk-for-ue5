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
#include "../Model/Contents.h"
#include "../Model/AcquireAction.h"
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::Quest::Request
{
    class FUpdateQuestModelMasterRequest;

    class GS2QUEST_API FUpdateQuestModelMasterRequest final : public TSharedFromThis<FUpdateQuestModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> QuestNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Model::FContents>>> ContentsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActionsValue;
        TSharedPtr<TArray<FString>> PremiseQuestNamesValue;
        
    public:
        
        FUpdateQuestModelMasterRequest();
        FUpdateQuestModelMasterRequest(
            const FUpdateQuestModelMasterRequest& From
        );
        ~FUpdateQuestModelMasterRequest() = default;

        TSharedPtr<FUpdateQuestModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithQuestName(const TOptional<FString> QuestName);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithContents(const TSharedPtr<TArray<TSharedPtr<Model::FContents>>> Contents);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithFirstCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FirstCompleteAcquireActions);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithFailedAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FailedAcquireActions);
        TSharedPtr<FUpdateQuestModelMasterRequest> WithPremiseQuestNames(
            const TSharedPtr<TArray<FString>> PremiseQuestNames);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetQuestName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;TSharedPtr<TArray<TSharedPtr<Model::FContents>>> GetContents() const;
        TOptional<FString> GetChallengePeriodEventId() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetFirstCompleteAcquireActions() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetConsumeActions() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetFailedAcquireActions() const;
        TSharedPtr<TArray<FString>> GetPremiseQuestNames() const;

        static TSharedPtr<FUpdateQuestModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateQuestModelMasterRequest> FUpdateQuestModelMasterRequestPtr;
}
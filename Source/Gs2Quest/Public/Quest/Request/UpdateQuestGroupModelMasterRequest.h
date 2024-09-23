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

namespace Gs2::Quest::Request
{
    class FUpdateQuestGroupModelMasterRequest;

    class GS2QUEST_API FUpdateQuestGroupModelMasterRequest final : public TSharedFromThis<FUpdateQuestGroupModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        
    public:
        
        FUpdateQuestGroupModelMasterRequest();
        FUpdateQuestGroupModelMasterRequest(
            const FUpdateQuestGroupModelMasterRequest& From
        );
        ~FUpdateQuestGroupModelMasterRequest() = default;

        TSharedPtr<FUpdateQuestGroupModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateQuestGroupModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateQuestGroupModelMasterRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FUpdateQuestGroupModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateQuestGroupModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateQuestGroupModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TSharedPtr<FUpdateQuestGroupModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateQuestGroupModelMasterRequest, ESPMode::ThreadSafe> FUpdateQuestGroupModelMasterRequestPtr;
}
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
    class FCreateQuestGroupModelMasterRequest;

    class GS2QUEST_API FCreateQuestGroupModelMasterRequest final : public TSharedFromThis<FCreateQuestGroupModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        
    public:
        
        FCreateQuestGroupModelMasterRequest();
        FCreateQuestGroupModelMasterRequest(
            const FCreateQuestGroupModelMasterRequest& From
        );
        ~FCreateQuestGroupModelMasterRequest() = default;

        TSharedPtr<FCreateQuestGroupModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateQuestGroupModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateQuestGroupModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateQuestGroupModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateQuestGroupModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateQuestGroupModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TSharedPtr<FCreateQuestGroupModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateQuestGroupModelMasterRequest, ESPMode::ThreadSafe> FCreateQuestGroupModelMasterRequestPtr;
}
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
#include "../Model/CounterScopeModel.h"

namespace Gs2::Mission::Request
{
    class FCreateCounterModelMasterRequest;

    class GS2MISSION_API FCreateCounterModelMasterRequest final : public TSharedFromThis<FCreateCounterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> ScopesValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        
    public:
        
        FCreateCounterModelMasterRequest();
        FCreateCounterModelMasterRequest(
            const FCreateCounterModelMasterRequest& From
        );
        ~FCreateCounterModelMasterRequest() = default;

        TSharedPtr<FCreateCounterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateCounterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateCounterModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateCounterModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateCounterModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateCounterModelMasterRequest> WithScopes(const TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> Scopes);
        TSharedPtr<FCreateCounterModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> GetScopes() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TSharedPtr<FCreateCounterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateCounterModelMasterRequest, ESPMode::ThreadSafe> FCreateCounterModelMasterRequestPtr;
}
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
    class FUpdateCounterModelMasterRequest;

    class GS2MISSION_API FUpdateCounterModelMasterRequest final : public TSharedFromThis<FUpdateCounterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> ScopesValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        
    public:
        
        FUpdateCounterModelMasterRequest();
        FUpdateCounterModelMasterRequest(
            const FUpdateCounterModelMasterRequest& From
        );
        ~FUpdateCounterModelMasterRequest() = default;

        TSharedPtr<FUpdateCounterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCounterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCounterModelMasterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FUpdateCounterModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateCounterModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateCounterModelMasterRequest> WithScopes(const TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> Scopes);
        TSharedPtr<FUpdateCounterModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> GetScopes() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TSharedPtr<FUpdateCounterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCounterModelMasterRequest, ESPMode::ThreadSafe> FUpdateCounterModelMasterRequestPtr;
}
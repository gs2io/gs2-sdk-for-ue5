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
#include "Mission/Model/CounterModel.h"
#include "Gs2MissionEzCounterScopeModel.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzCounterModel final : public TSharedFromThis<FEzCounterModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterScopeModel>>> ScopesValue;
        TOptional<FString> ChallengePeriodEventIdValue;

	public:
        TSharedPtr<FEzCounterModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzCounterModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzCounterModel> WithScopes(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterScopeModel>>> Scopes);
        TSharedPtr<FEzCounterModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterScopeModel>>> GetScopes() const;

        TOptional<FString> GetChallengePeriodEventId() const;

        Gs2::Mission::Model::FCounterModelPtr ToModel() const;
        static TSharedPtr<FEzCounterModel> FromModel(Gs2::Mission::Model::FCounterModelPtr Model);
    };
    typedef TSharedPtr<FEzCounterModel> FEzCounterModelPtr;
}
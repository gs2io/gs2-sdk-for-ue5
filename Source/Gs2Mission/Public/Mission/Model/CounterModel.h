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
#include "Core/Gs2Object.h"
#include "CounterScopeModel.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FCounterModel final : public FGs2Object, public TSharedFromThis<FCounterModel>
    {
        TOptional<FString> CounterIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FCounterScopeModel>>> ScopesValue;
        TOptional<FString> ChallengePeriodEventIdValue;

    public:
        FCounterModel();
        FCounterModel(
            const FCounterModel& From
        );
        virtual ~FCounterModel() override = default;

        TSharedPtr<FCounterModel> WithCounterId(const TOptional<FString> CounterId);
        TSharedPtr<FCounterModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FCounterModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCounterModel> WithScopes(const TSharedPtr<TArray<TSharedPtr<FCounterScopeModel>>> Scopes);
        TSharedPtr<FCounterModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetCounterId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FCounterScopeModel>>> GetScopes() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCounterNameFromGrn(const FString Grn);

        static TSharedPtr<FCounterModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCounterModel, ESPMode::ThreadSafe> FCounterModelPtr;
}
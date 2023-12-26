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
#include "Grade/Model/GradeModel.h"
#include "Gs2GradeEzGradeEntryModel.h"
#include "Gs2GradeEzAcquireActionRate.h"

namespace Gs2::UE5::Grade::Model
{
	class EZGS2_API FEzGradeModel final : public TSharedFromThis<FEzGradeModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeEntryModel>>> GradeEntriesValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzAcquireActionRate>>> AcquireActionRatesValue;

	public:
        TSharedPtr<FEzGradeModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzGradeModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzGradeModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FEzGradeModel> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeEntryModel>>> GradeEntries);
        TSharedPtr<FEzGradeModel> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetExperienceModelId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzGradeEntryModel>>> GetGradeEntries() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Grade::Model::FEzAcquireActionRate>>> GetAcquireActionRates() const;

        Gs2::Grade::Model::FGradeModelPtr ToModel() const;
        static TSharedPtr<FEzGradeModel> FromModel(Gs2::Grade::Model::FGradeModelPtr Model);
    };
    typedef TSharedPtr<FEzGradeModel> FEzGradeModelPtr;
}
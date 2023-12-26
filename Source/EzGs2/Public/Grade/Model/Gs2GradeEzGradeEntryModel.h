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
#include "Grade/Model/GradeEntryModel.h"

namespace Gs2::UE5::Grade::Model
{
	class EZGS2_API FEzGradeEntryModel final : public TSharedFromThis<FEzGradeEntryModel>
	{
        TOptional<FString> MetadataValue;
        TOptional<int64> RankCapValueValue;

	public:
        TSharedPtr<FEzGradeEntryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzGradeEntryModel> WithRankCapValue(const TOptional<int64> RankCapValue);

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;

        Gs2::Grade::Model::FGradeEntryModelPtr ToModel() const;
        static TSharedPtr<FEzGradeEntryModel> FromModel(Gs2::Grade::Model::FGradeEntryModelPtr Model);
    };
    typedef TSharedPtr<FEzGradeEntryModel> FEzGradeEntryModelPtr;
}
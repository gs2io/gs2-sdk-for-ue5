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
#include "Grade/Model/Status.h"

namespace Gs2::UE5::Grade::Model
{
	class EZGS2_API FEzStatus final : public TSharedFromThis<FEzStatus>
	{
        TOptional<FString> GradeNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> GradeValueValue;

	public:
        TSharedPtr<FEzStatus> WithGradeName(const TOptional<FString> GradeName);
        TSharedPtr<FEzStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FEzStatus> WithGradeValue(const TOptional<int64> GradeValue);

        TOptional<FString> GetGradeName() const;

        TOptional<FString> GetPropertyId() const;

        TOptional<int64> GetGradeValue() const;
        FString GetGradeValueString() const;

        Gs2::Grade::Model::FStatusPtr ToModel() const;
        static TSharedPtr<FEzStatus> FromModel(Gs2::Grade::Model::FStatusPtr Model);
    };
    typedef TSharedPtr<FEzStatus> FEzStatusPtr;
}
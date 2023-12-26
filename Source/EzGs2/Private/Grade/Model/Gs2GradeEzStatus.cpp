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

#include "Grade/Model/Gs2GradeEzStatus.h"

namespace Gs2::UE5::Grade::Model
{

    TSharedPtr<FEzStatus> FEzStatus::WithGradeName(
        const TOptional<FString> GradeName
    )
    {
        this->GradeNameValue = GradeName;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }
    TOptional<FString> FEzStatus::GetGradeName() const
    {
        return GradeNameValue;
    }
    TOptional<FString> FEzStatus::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TOptional<int64> FEzStatus::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FEzStatus::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }

    Gs2::Grade::Model::FStatusPtr FEzStatus::ToModel() const
    {
        return MakeShared<Gs2::Grade::Model::FStatus>()
            ->WithGradeName(GradeNameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithGradeValue(GradeValueValue);
    }

    TSharedPtr<FEzStatus> FEzStatus::FromModel(const Gs2::Grade::Model::FStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStatus>()
            ->WithGradeName(Model->GetGradeName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithGradeValue(Model->GetGradeValue());
    }
}
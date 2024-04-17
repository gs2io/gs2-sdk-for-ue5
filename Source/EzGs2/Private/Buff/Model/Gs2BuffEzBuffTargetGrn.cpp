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

#include "Buff/Model/Gs2BuffEzBuffTargetGrn.h"

namespace Gs2::UE5::Buff::Model
{

    TSharedPtr<FEzBuffTargetGrn> FEzBuffTargetGrn::WithTargetModelName(
        const TOptional<FString> TargetModelName
    )
    {
        this->TargetModelNameValue = TargetModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffTargetGrn> FEzBuffTargetGrn::WithTargetGrn(
        const TOptional<FString> TargetGrn
    )
    {
        this->TargetGrnValue = TargetGrn;
        return SharedThis(this);
    }
    TOptional<FString> FEzBuffTargetGrn::GetTargetModelName() const
    {
        return TargetModelNameValue;
    }
    TOptional<FString> FEzBuffTargetGrn::GetTargetGrn() const
    {
        return TargetGrnValue;
    }

    Gs2::Buff::Model::FBuffTargetGrnPtr FEzBuffTargetGrn::ToModel() const
    {
        return MakeShared<Gs2::Buff::Model::FBuffTargetGrn>()
            ->WithTargetModelName(TargetModelNameValue)
            ->WithTargetGrn(TargetGrnValue);
    }

    TSharedPtr<FEzBuffTargetGrn> FEzBuffTargetGrn::FromModel(const Gs2::Buff::Model::FBuffTargetGrnPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBuffTargetGrn>()
            ->WithTargetModelName(Model->GetTargetModelName())
            ->WithTargetGrn(Model->GetTargetGrn());
    }
}
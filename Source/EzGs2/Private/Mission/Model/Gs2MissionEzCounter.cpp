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

#include "Mission/Model/Gs2MissionEzCounter.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzCounter> FEzCounter::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounter> FEzCounter::WithValues(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzScopedValue>>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<FString> FEzCounter::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzScopedValue>>> FEzCounter::GetValues() const
    {
        return ValuesValue;
    }

    Gs2::Mission::Model::FCounterPtr FEzCounter::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FCounter>()
            ->WithName(NameValue)
            ->WithValues([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Mission::Model::FScopedValue>>>();
                    if (ValuesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ValuesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzCounter> FEzCounter::FromModel(const Gs2::Mission::Model::FCounterPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCounter>()
            ->WithName(Model->GetName())
            ->WithValues([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzScopedValue>>>();
                    if (Model->GetValues() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetValues())
                    {
                        v->Add(FEzScopedValue::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}
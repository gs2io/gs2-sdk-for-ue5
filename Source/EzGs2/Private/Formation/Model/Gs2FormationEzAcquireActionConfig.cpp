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

#include "EzGs2/Public/Formation/Model/Gs2FormationEzAcquireActionConfig.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzAcquireActionConfig> FEzAcquireActionConfig::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionConfig> FEzAcquireActionConfig::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }
    TOptional<FString> FEzAcquireActionConfig::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzConfig>>> FEzAcquireActionConfig::GetConfig() const
    {
        return ConfigValue;
    }

    Gs2::Formation::Model::FAcquireActionConfigPtr FEzAcquireActionConfig::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FAcquireActionConfig>()
            ->WithName(NameValue)
            ->WithConfig([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Formation::Model::FConfig>>>();
                    if (ConfigValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConfigValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzAcquireActionConfig> FEzAcquireActionConfig::FromModel(const Gs2::Formation::Model::FAcquireActionConfigPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAcquireActionConfig>()
            ->WithName(Model->GetName())
            ->WithConfig([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConfig>>>();
                    if (Model->GetConfig() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConfig())
                    {
                        v->Add(FEzConfig::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}
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

#include "Dictionary/Model/Gs2DictionaryEzConfig.h"

namespace Gs2::UE5::Dictionary::Model
{

    TSharedPtr<FEzConfig> FEzConfig::WithKey(
        const TOptional<FString> Key
    )
    {
        this->KeyValue = Key;
        return SharedThis(this);
    }

    TSharedPtr<FEzConfig> FEzConfig::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzConfig::GetKey() const
    {
        return KeyValue;
    }
    TOptional<FString> FEzConfig::GetValue() const
    {
        return ValueValue;
    }

    Gs2::Dictionary::Model::FConfigPtr FEzConfig::ToModel() const
    {
        return MakeShared<Gs2::Dictionary::Model::FConfig>()
            ->WithKey(KeyValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzConfig> FEzConfig::FromModel(const Gs2::Dictionary::Model::FConfigPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzConfig>()
            ->WithKey(Model->GetKey())
            ->WithValue(Model->GetValue());
    }
}
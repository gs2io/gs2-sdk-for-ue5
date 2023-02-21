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

#include "EzGs2/Public/Matchmaking/Model/Gs2MatchmakingEzAttribute.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzAttribute> FEzAttribute::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzAttribute> FEzAttribute::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzAttribute::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FEzAttribute::GetValue() const
    {
        return ValueValue;
    }

    FString FEzAttribute::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ValueValue.GetValue());
    }

    Gs2::Matchmaking::Model::FAttributePtr FEzAttribute::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FAttribute>()
            ->WithName(NameValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzAttribute> FEzAttribute::FromModel(const Gs2::Matchmaking::Model::FAttributePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAttribute>()
            ->WithName(Model->GetName())
            ->WithValue(Model->GetValue());
    }
}
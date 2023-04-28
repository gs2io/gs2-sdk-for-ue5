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

#include "EzGs2/Public/Formation/Model/Gs2FormationEzMold.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzMold> FEzMold::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMold> FEzMold::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMold> FEzMold::WithCapacity(
        const TOptional<int32> Capacity
    )
    {
        this->CapacityValue = Capacity;
        return SharedThis(this);
    }
    TOptional<FString> FEzMold::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMold::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FEzMold::GetCapacity() const
    {
        return CapacityValue;
    }

    FString FEzMold::GetCapacityString() const
    {
        if (!CapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CapacityValue.GetValue());
    }

    Gs2::Formation::Model::FMoldPtr FEzMold::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FMold>()
            ->WithName(NameValue)
            ->WithUserId(UserIdValue)
            ->WithCapacity(CapacityValue);
    }

    TSharedPtr<FEzMold> FEzMold::FromModel(const Gs2::Formation::Model::FMoldPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMold>()
            ->WithName(Model->GetName())
            ->WithUserId(Model->GetUserId())
            ->WithCapacity(Model->GetCapacity());
    }
}
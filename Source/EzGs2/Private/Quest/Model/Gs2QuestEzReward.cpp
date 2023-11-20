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

#include "Quest/Model/Gs2QuestEzReward.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzReward> FEzReward::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FEzReward> FEzReward::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }

    TSharedPtr<FEzReward> FEzReward::WithItemId(
        const TOptional<FString> ItemId
    )
    {
        this->ItemIdValue = ItemId;
        return SharedThis(this);
    }

    TSharedPtr<FEzReward> FEzReward::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzReward::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FEzReward::GetRequest() const
    {
        return RequestValue;
    }
    TOptional<FString> FEzReward::GetItemId() const
    {
        return ItemIdValue;
    }
    TOptional<int32> FEzReward::GetValue() const
    {
        return ValueValue;
    }

    FString FEzReward::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }

    Gs2::Quest::Model::FRewardPtr FEzReward::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FReward>()
            ->WithAction(ActionValue)
            ->WithRequest(RequestValue)
            ->WithItemId(ItemIdValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzReward> FEzReward::FromModel(const Gs2::Quest::Model::FRewardPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzReward>()
            ->WithAction(Model->GetAction())
            ->WithRequest(Model->GetRequest())
            ->WithItemId(Model->GetItemId())
            ->WithValue(Model->GetValue());
    }
}
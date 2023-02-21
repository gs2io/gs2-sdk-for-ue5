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

#include "EzGs2/Public/Exchange/Model/Gs2ExchangeEzConsumeAction.h"

namespace Gs2::UE5::Exchange::Model
{

    TSharedPtr<FEzConsumeAction> FEzConsumeAction::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FEzConsumeAction> FEzConsumeAction::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }
    TOptional<FString> FEzConsumeAction::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FEzConsumeAction::GetRequest() const
    {
        return RequestValue;
    }

    Gs2::Exchange::Model::FConsumeActionPtr FEzConsumeAction::ToModel() const
    {
        return MakeShared<Gs2::Exchange::Model::FConsumeAction>()
            ->WithAction(ActionValue)
            ->WithRequest(RequestValue);
    }

    TSharedPtr<FEzConsumeAction> FEzConsumeAction::FromModel(const Gs2::Exchange::Model::FConsumeActionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzConsumeAction>()
            ->WithAction(Model->GetAction())
            ->WithRequest(Model->GetRequest());
    }
}
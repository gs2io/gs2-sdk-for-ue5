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

#include "Distributor/Model/Gs2DistributorEzVerifyAction.h"

namespace Gs2::UE5::Distributor::Model
{

    TSharedPtr<FEzVerifyAction> FEzVerifyAction::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FEzVerifyAction> FEzVerifyAction::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }
    TOptional<FString> FEzVerifyAction::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FEzVerifyAction::GetRequest() const
    {
        return RequestValue;
    }

    Gs2::Distributor::Model::FVerifyActionPtr FEzVerifyAction::ToModel() const
    {
        return MakeShared<Gs2::Distributor::Model::FVerifyAction>()
            ->WithAction(ActionValue)
            ->WithRequest(RequestValue);
    }

    TSharedPtr<FEzVerifyAction> FEzVerifyAction::FromModel(const Gs2::Distributor::Model::FVerifyActionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzVerifyAction>()
            ->WithAction(Model->GetAction())
            ->WithRequest(Model->GetRequest());
    }
}
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

#include "Quest/Model/Gs2QuestEzConsumeActionResult.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithConsumeRequest(
        const TOptional<FString> ConsumeRequest
    )
    {
        this->ConsumeRequestValue = ConsumeRequest;
        return SharedThis(this);
    }

    TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithConsumeResult(
        const TOptional<FString> ConsumeResult
    )
    {
        this->ConsumeResultValue = ConsumeResult;
        return SharedThis(this);
    }
    TOptional<FString> FEzConsumeActionResult::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FEzConsumeActionResult::GetConsumeRequest() const
    {
        return ConsumeRequestValue;
    }
    TOptional<int32> FEzConsumeActionResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FEzConsumeActionResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FEzConsumeActionResult::GetConsumeResult() const
    {
        return ConsumeResultValue;
    }

    Gs2::Quest::Model::FConsumeActionResultPtr FEzConsumeActionResult::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FConsumeActionResult>()
            ->WithAction(ActionValue)
            ->WithConsumeRequest(ConsumeRequestValue)
            ->WithStatusCode(StatusCodeValue)
            ->WithConsumeResult(ConsumeResultValue);
    }

    TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::FromModel(const Gs2::Quest::Model::FConsumeActionResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzConsumeActionResult>()
            ->WithAction(Model->GetAction())
            ->WithConsumeRequest(Model->GetConsumeRequest())
            ->WithStatusCode(Model->GetStatusCode())
            ->WithConsumeResult(Model->GetConsumeResult());
    }
}
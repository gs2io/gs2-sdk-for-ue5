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

#include "Guild/Model/Gs2GuildEzVerifyActionResult.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithVerifyRequest(
        const TOptional<FString> VerifyRequest
    )
    {
        this->VerifyRequestValue = VerifyRequest;
        return SharedThis(this);
    }

    TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithVerifyResult(
        const TOptional<FString> VerifyResult
    )
    {
        this->VerifyResultValue = VerifyResult;
        return SharedThis(this);
    }
    TOptional<FString> FEzVerifyActionResult::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FEzVerifyActionResult::GetVerifyRequest() const
    {
        return VerifyRequestValue;
    }
    TOptional<int32> FEzVerifyActionResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FEzVerifyActionResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FEzVerifyActionResult::GetVerifyResult() const
    {
        return VerifyResultValue;
    }

    Gs2::Guild::Model::FVerifyActionResultPtr FEzVerifyActionResult::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FVerifyActionResult>()
            ->WithAction(ActionValue)
            ->WithVerifyRequest(VerifyRequestValue)
            ->WithStatusCode(StatusCodeValue)
            ->WithVerifyResult(VerifyResultValue);
    }

    TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::FromModel(const Gs2::Guild::Model::FVerifyActionResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzVerifyActionResult>()
            ->WithAction(Model->GetAction())
            ->WithVerifyRequest(Model->GetVerifyRequest())
            ->WithStatusCode(Model->GetStatusCode())
            ->WithVerifyResult(Model->GetVerifyResult());
    }
}
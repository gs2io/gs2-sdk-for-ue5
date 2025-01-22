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

#include "Experience/Model/Gs2ExperienceEzAcquireActionResult.h"

namespace Gs2::UE5::Experience::Model
{

    TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithAcquireRequest(
        const TOptional<FString> AcquireRequest
    )
    {
        this->AcquireRequestValue = AcquireRequest;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithStatusCode(
        const TOptional<int32> StatusCode
    )
    {
        this->StatusCodeValue = StatusCode;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithAcquireResult(
        const TOptional<FString> AcquireResult
    )
    {
        this->AcquireResultValue = AcquireResult;
        return SharedThis(this);
    }
    TOptional<FString> FEzAcquireActionResult::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FEzAcquireActionResult::GetAcquireRequest() const
    {
        return AcquireRequestValue;
    }
    TOptional<int32> FEzAcquireActionResult::GetStatusCode() const
    {
        return StatusCodeValue;
    }

    FString FEzAcquireActionResult::GetStatusCodeString() const
    {
        if (!StatusCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StatusCodeValue.GetValue());
    }
    TOptional<FString> FEzAcquireActionResult::GetAcquireResult() const
    {
        return AcquireResultValue;
    }

    Gs2::Experience::Model::FAcquireActionResultPtr FEzAcquireActionResult::ToModel() const
    {
        return MakeShared<Gs2::Experience::Model::FAcquireActionResult>()
            ->WithAction(ActionValue)
            ->WithAcquireRequest(AcquireRequestValue)
            ->WithStatusCode(StatusCodeValue)
            ->WithAcquireResult(AcquireResultValue);
    }

    TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::FromModel(const Gs2::Experience::Model::FAcquireActionResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAcquireActionResult>()
            ->WithAction(Model->GetAction())
            ->WithAcquireRequest(Model->GetAcquireRequest())
            ->WithStatusCode(Model->GetStatusCode())
            ->WithAcquireResult(Model->GetAcquireResult());
    }
}
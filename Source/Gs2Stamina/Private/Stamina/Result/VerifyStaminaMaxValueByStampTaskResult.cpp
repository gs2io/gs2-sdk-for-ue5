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

#include "Stamina/Result/VerifyStaminaMaxValueByStampTaskResult.h"

namespace Gs2::Stamina::Result
{
    FVerifyStaminaMaxValueByStampTaskResult::FVerifyStaminaMaxValueByStampTaskResult():
        NewContextStackValue(TOptional<FString>())
    {
    }

    FVerifyStaminaMaxValueByStampTaskResult::FVerifyStaminaMaxValueByStampTaskResult(
        const FVerifyStaminaMaxValueByStampTaskResult& From
    ):
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FVerifyStaminaMaxValueByStampTaskResult> FVerifyStaminaMaxValueByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyStaminaMaxValueByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FVerifyStaminaMaxValueByStampTaskResult> FVerifyStaminaMaxValueByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyStaminaMaxValueByStampTaskResult>()
            ->WithNewContextStack(Data->HasField(ANSI_TO_TCHAR("newContextStack")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("newContextStack"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyStaminaMaxValueByStampTaskResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NewContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("newContextStack", NewContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}
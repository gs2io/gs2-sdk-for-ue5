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

#include "Distributor/Result/RunStampTaskWithoutNamespaceResult.h"

namespace Gs2::Distributor::Result
{
    FRunStampTaskWithoutNamespaceResult::FRunStampTaskWithoutNamespaceResult():
        ContextStackValue(TOptional<FString>()),
        ResultValue(TOptional<FString>())
    {
    }

    FRunStampTaskWithoutNamespaceResult::FRunStampTaskWithoutNamespaceResult(
        const FRunStampTaskWithoutNamespaceResult& From
    ):
        ContextStackValue(From.ContextStackValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FRunStampTaskWithoutNamespaceResult> FRunStampTaskWithoutNamespaceResult::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampTaskWithoutNamespaceResult> FRunStampTaskWithoutNamespaceResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TOptional<FString> FRunStampTaskWithoutNamespaceResult::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FRunStampTaskWithoutNamespaceResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FRunStampTaskWithoutNamespaceResult> FRunStampTaskWithoutNamespaceResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunStampTaskWithoutNamespaceResult>()
            ->WithContextStack(Data->HasField("contextStack") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("contextStack", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResult(Data->HasField("result") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("result", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunStampTaskWithoutNamespaceResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        return JsonRootObject;
    }
}
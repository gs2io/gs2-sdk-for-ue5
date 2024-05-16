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

#include "Quest/Result/GetNamespaceStatusResult.h"

namespace Gs2::Quest::Result
{
    FGetNamespaceStatusResult::FGetNamespaceStatusResult():
        StatusValue(TOptional<FString>())
    {
    }

    FGetNamespaceStatusResult::FGetNamespaceStatusResult(
        const FGetNamespaceStatusResult& From
    ):
        StatusValue(From.StatusValue)
    {
    }

    TSharedPtr<FGetNamespaceStatusResult> FGetNamespaceStatusResult::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TOptional<FString> FGetNamespaceStatusResult::GetStatus() const
    {
        return StatusValue;
    }

    TSharedPtr<FGetNamespaceStatusResult> FGetNamespaceStatusResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetNamespaceStatusResult>()
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("status"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetNamespaceStatusResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        return JsonRootObject;
    }
}
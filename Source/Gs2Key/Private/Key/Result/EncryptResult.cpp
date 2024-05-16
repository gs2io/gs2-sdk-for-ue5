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

#include "Key/Result/EncryptResult.h"

namespace Gs2::Key::Result
{
    FEncryptResult::FEncryptResult():
        DataValue(TOptional<FString>())
    {
    }

    FEncryptResult::FEncryptResult(
        const FEncryptResult& From
    ):
        DataValue(From.DataValue)
    {
    }

    TSharedPtr<FEncryptResult> FEncryptResult::WithData(
        const TOptional<FString> Data
    )
    {
        this->DataValue = Data;
        return SharedThis(this);
    }

    TOptional<FString> FEncryptResult::GetData() const
    {
        return DataValue;
    }

    TSharedPtr<FEncryptResult> FEncryptResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEncryptResult>()
            ->WithData(Data->HasField(ANSI_TO_TCHAR("data")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("data"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FEncryptResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DataValue.IsSet())
        {
            JsonRootObject->SetStringField("data", DataValue.GetValue());
        }
        return JsonRootObject;
    }
}
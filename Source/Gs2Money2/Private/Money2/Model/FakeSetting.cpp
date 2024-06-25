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

#include "Money2/Model/FakeSetting.h"

namespace Gs2::Money2::Model
{
    FFakeSetting::FFakeSetting():
        AcceptFakeReceiptValue(TOptional<FString>())
    {
    }

    FFakeSetting::FFakeSetting(
        const FFakeSetting& From
    ):
        AcceptFakeReceiptValue(From.AcceptFakeReceiptValue)
    {
    }

    TSharedPtr<FFakeSetting> FFakeSetting::WithAcceptFakeReceipt(
        const TOptional<FString> AcceptFakeReceipt
    )
    {
        this->AcceptFakeReceiptValue = AcceptFakeReceipt;
        return SharedThis(this);
    }
    TOptional<FString> FFakeSetting::GetAcceptFakeReceipt() const
    {
        return AcceptFakeReceiptValue;
    }

    TSharedPtr<FFakeSetting> FFakeSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFakeSetting>()
            ->WithAcceptFakeReceipt(Data->HasField(ANSI_TO_TCHAR("acceptFakeReceipt")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("acceptFakeReceipt"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FFakeSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AcceptFakeReceiptValue.IsSet())
        {
            JsonRootObject->SetStringField("acceptFakeReceipt", AcceptFakeReceiptValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FFakeSetting::TypeName = "FakeSetting";
}
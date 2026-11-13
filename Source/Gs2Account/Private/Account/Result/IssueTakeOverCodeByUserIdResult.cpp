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

#include "Account/Result/IssueTakeOverCodeByUserIdResult.h"

namespace Gs2::Account::Result
{
    FIssueTakeOverCodeByUserIdResult::FIssueTakeOverCodeByUserIdResult():
        ItemValue(nullptr),
        PasswordValue(TOptional<FString>())
    {
    }

    FIssueTakeOverCodeByUserIdResult::FIssueTakeOverCodeByUserIdResult(
        const FIssueTakeOverCodeByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        PasswordValue(From.PasswordValue)
    {
    }

    TSharedPtr<FIssueTakeOverCodeByUserIdResult> FIssueTakeOverCodeByUserIdResult::WithItem(
        const TSharedPtr<Model::FTakeOver> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FIssueTakeOverCodeByUserIdResult> FIssueTakeOverCodeByUserIdResult::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<Model::FTakeOver> FIssueTakeOverCodeByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FIssueTakeOverCodeByUserIdResult::GetPassword() const
    {
        return PasswordValue;
    }

    TSharedPtr<FIssueTakeOverCodeByUserIdResult> FIssueTakeOverCodeByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIssueTakeOverCodeByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FTakeOverPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FTakeOver::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithPassword(Data->HasField(ANSI_TO_TCHAR("password")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("password"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FIssueTakeOverCodeByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("item"), ItemValue->ToJson());
        }
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("password"), PasswordValue.GetValue());
        }
        return JsonRootObject;
    }
}
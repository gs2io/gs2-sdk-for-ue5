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

#include "Account/Result/PreviewTakeOverOpenIdConnectResult.h"

namespace Gs2::Account::Result
{
    FPreviewTakeOverOpenIdConnectResult::FPreviewTakeOverOpenIdConnectResult():
        ItemValue(nullptr),
        BanStatusesValue(nullptr),
        TokenValue(TOptional<FString>()),
        ExpireValue(TOptional<int64>())
    {
    }

    FPreviewTakeOverOpenIdConnectResult::FPreviewTakeOverOpenIdConnectResult(
        const FPreviewTakeOverOpenIdConnectResult& From
    ):
        ItemValue(From.ItemValue),
        BanStatusesValue(From.BanStatusesValue),
        TokenValue(From.TokenValue),
        ExpireValue(From.ExpireValue)
    {
    }

    TSharedPtr<FPreviewTakeOverOpenIdConnectResult> FPreviewTakeOverOpenIdConnectResult::WithItem(
        const TSharedPtr<Model::FAccount> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FPreviewTakeOverOpenIdConnectResult> FPreviewTakeOverOpenIdConnectResult::WithBanStatuses(
        const TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> BanStatuses
    )
    {
        this->BanStatusesValue = BanStatuses;
        return SharedThis(this);
    }

    TSharedPtr<FPreviewTakeOverOpenIdConnectResult> FPreviewTakeOverOpenIdConnectResult::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FPreviewTakeOverOpenIdConnectResult> FPreviewTakeOverOpenIdConnectResult::WithExpire(
        const TOptional<int64> Expire
    )
    {
        this->ExpireValue = Expire;
        return SharedThis(this);
    }

    TSharedPtr<Model::FAccount> FPreviewTakeOverOpenIdConnectResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> FPreviewTakeOverOpenIdConnectResult::GetBanStatuses() const
    {
        if (!BanStatusesValue.IsValid())
        {
            return nullptr;
        }
        return BanStatusesValue;
    }

    TOptional<FString> FPreviewTakeOverOpenIdConnectResult::GetToken() const
    {
        return TokenValue;
    }

    TOptional<int64> FPreviewTakeOverOpenIdConnectResult::GetExpire() const
    {
        return ExpireValue;
    }

    FString FPreviewTakeOverOpenIdConnectResult::GetExpireString() const
    {
        if (!ExpireValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpireValue.GetValue());
    }

    TSharedPtr<FPreviewTakeOverOpenIdConnectResult> FPreviewTakeOverOpenIdConnectResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPreviewTakeOverOpenIdConnectResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FAccountPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FAccount::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithBanStatuses(Data->HasField(ANSI_TO_TCHAR("banStatuses")) ? [Data]() -> TSharedPtr<TArray<Model::FBanStatusPtr>>
                 {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("banStatuses")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FBanStatusPtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("banStatuses")))
                    {
                        v->Add(Model::FBanStatus::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr)
            ->WithToken(Data->HasField(ANSI_TO_TCHAR("token")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("token"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpire(Data->HasField(ANSI_TO_TCHAR("expire")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expire"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FPreviewTakeOverOpenIdConnectResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("item"), ItemValue->ToJson());
        }
        if (BanStatusesValue != nullptr && BanStatusesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *BanStatusesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("banStatuses"), v);
        }
        if (TokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("token"), TokenValue.GetValue());
        }
        if (ExpireValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("expire"), FString::Printf(TEXT("%lld"), ExpireValue.GetValue()));
        }
        return JsonRootObject;
    }
}
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

#include "News/Result/WantGrantByUserIdResult.h"

namespace Gs2::News::Result
{
    FWantGrantByUserIdResult::FWantGrantByUserIdResult():
        ItemsValue(nullptr),
        BrowserUrlValue(TOptional<FString>()),
        ZipUrlValue(TOptional<FString>())
    {
    }

    FWantGrantByUserIdResult::FWantGrantByUserIdResult(
        const FWantGrantByUserIdResult& From
    ):
        ItemsValue(From.ItemsValue),
        BrowserUrlValue(From.BrowserUrlValue),
        ZipUrlValue(From.ZipUrlValue)
    {
    }

    TSharedPtr<FWantGrantByUserIdResult> FWantGrantByUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FSetCookieRequestEntry>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FWantGrantByUserIdResult> FWantGrantByUserIdResult::WithBrowserUrl(
        const TOptional<FString> BrowserUrl
    )
    {
        this->BrowserUrlValue = BrowserUrl;
        return SharedThis(this);
    }

    TSharedPtr<FWantGrantByUserIdResult> FWantGrantByUserIdResult::WithZipUrl(
        const TOptional<FString> ZipUrl
    )
    {
        this->ZipUrlValue = ZipUrl;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSetCookieRequestEntry>>> FWantGrantByUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FWantGrantByUserIdResult::GetBrowserUrl() const
    {
        return BrowserUrlValue;
    }

    TOptional<FString> FWantGrantByUserIdResult::GetZipUrl() const
    {
        return ZipUrlValue;
    }

    TSharedPtr<FWantGrantByUserIdResult> FWantGrantByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWantGrantByUserIdResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FSetCookieRequestEntryPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FSetCookieRequestEntryPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FSetCookieRequestEntry::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSetCookieRequestEntryPtr>>())
            ->WithBrowserUrl(Data->HasField("browserUrl") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("browserUrl", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithZipUrl(Data->HasField("zipUrl") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("zipUrl", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FWantGrantByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemsValue != nullptr && ItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("items", v);
        }
        if (BrowserUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("browserUrl", BrowserUrlValue.GetValue());
        }
        if (ZipUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("zipUrl", ZipUrlValue.GetValue());
        }
        return JsonRootObject;
    }
}
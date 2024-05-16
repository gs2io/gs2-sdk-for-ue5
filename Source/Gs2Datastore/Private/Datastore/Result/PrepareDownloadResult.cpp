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

#include "Datastore/Result/PrepareDownloadResult.h"

namespace Gs2::Datastore::Result
{
    FPrepareDownloadResult::FPrepareDownloadResult():
        ItemValue(nullptr),
        FileUrlValue(TOptional<FString>()),
        ContentLengthValue(TOptional<int64>())
    {
    }

    FPrepareDownloadResult::FPrepareDownloadResult(
        const FPrepareDownloadResult& From
    ):
        ItemValue(From.ItemValue),
        FileUrlValue(From.FileUrlValue),
        ContentLengthValue(From.ContentLengthValue)
    {
    }

    TSharedPtr<FPrepareDownloadResult> FPrepareDownloadResult::WithItem(
        const TSharedPtr<Model::FDataObject> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadResult> FPrepareDownloadResult::WithFileUrl(
        const TOptional<FString> FileUrl
    )
    {
        this->FileUrlValue = FileUrl;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadResult> FPrepareDownloadResult::WithContentLength(
        const TOptional<int64> ContentLength
    )
    {
        this->ContentLengthValue = ContentLength;
        return SharedThis(this);
    }

    TSharedPtr<Model::FDataObject> FPrepareDownloadResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FPrepareDownloadResult::GetFileUrl() const
    {
        return FileUrlValue;
    }

    TOptional<int64> FPrepareDownloadResult::GetContentLength() const
    {
        return ContentLengthValue;
    }

    FString FPrepareDownloadResult::GetContentLengthString() const
    {
        if (!ContentLengthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ContentLengthValue.GetValue());
    }

    TSharedPtr<FPrepareDownloadResult> FPrepareDownloadResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareDownloadResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FDataObjectPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FDataObject::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithFileUrl(Data->HasField(ANSI_TO_TCHAR("fileUrl")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("fileUrl"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContentLength(Data->HasField(ANSI_TO_TCHAR("contentLength")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("contentLength"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FPrepareDownloadResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (FileUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("fileUrl", FileUrlValue.GetValue());
        }
        if (ContentLengthValue.IsSet())
        {
            JsonRootObject->SetStringField("contentLength", FString::Printf(TEXT("%lld"), ContentLengthValue.GetValue()));
        }
        return JsonRootObject;
    }
}
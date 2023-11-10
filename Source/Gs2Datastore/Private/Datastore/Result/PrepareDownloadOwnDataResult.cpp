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

#include "Datastore/Result/PrepareDownloadOwnDataResult.h"

namespace Gs2::Datastore::Result
{
    FPrepareDownloadOwnDataResult::FPrepareDownloadOwnDataResult():
        ItemValue(nullptr),
        FileUrlValue(TOptional<FString>()),
        ContentLengthValue(TOptional<int64>())
    {
    }

    FPrepareDownloadOwnDataResult::FPrepareDownloadOwnDataResult(
        const FPrepareDownloadOwnDataResult& From
    ):
        ItemValue(From.ItemValue),
        FileUrlValue(From.FileUrlValue),
        ContentLengthValue(From.ContentLengthValue)
    {
    }

    TSharedPtr<FPrepareDownloadOwnDataResult> FPrepareDownloadOwnDataResult::WithItem(
        const TSharedPtr<Model::FDataObject> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadOwnDataResult> FPrepareDownloadOwnDataResult::WithFileUrl(
        const TOptional<FString> FileUrl
    )
    {
        this->FileUrlValue = FileUrl;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadOwnDataResult> FPrepareDownloadOwnDataResult::WithContentLength(
        const TOptional<int64> ContentLength
    )
    {
        this->ContentLengthValue = ContentLength;
        return SharedThis(this);
    }

    TSharedPtr<Model::FDataObject> FPrepareDownloadOwnDataResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FPrepareDownloadOwnDataResult::GetFileUrl() const
    {
        return FileUrlValue;
    }

    TOptional<int64> FPrepareDownloadOwnDataResult::GetContentLength() const
    {
        return ContentLengthValue;
    }

    FString FPrepareDownloadOwnDataResult::GetContentLengthString() const
    {
        if (!ContentLengthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ContentLengthValue.GetValue());
    }

    TSharedPtr<FPrepareDownloadOwnDataResult> FPrepareDownloadOwnDataResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareDownloadOwnDataResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FDataObjectPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FDataObject::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithFileUrl(Data->HasField("fileUrl") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("fileUrl", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContentLength(Data->HasField("contentLength") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("contentLength", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FPrepareDownloadOwnDataResult::ToJson() const
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